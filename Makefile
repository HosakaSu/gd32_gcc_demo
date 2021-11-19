#工程名称
TARGET 			= manual_board_gd32
INTERFACE_CFG = /usr/share/openocd/scripts/interface/stlink.cfg
TARGET_CFG = /usr/share/openocd/scripts/target/stm32f1x.cfg
PWD = $(shell pwd)
#设置编译器
CC     			= arm-none-eabi-gcc
OBJCOPY			= arm-none-eabi-objcopy
ARMSIZE			= arm-none-eabi-size

#获取当前工作目录
TOP=.

#设置源文件后缀，c或cpp
EXT				= c

#设置源文件搜索路径
VPATH			+= $(TOP)/user
VPATH 			+= $(TOP)/core/cmsis/GD/GD32F10x/Source
VPATH			+= $(TOP)/core/gd32f10x_standard_peripheral/Source
VPATH			+= $(TOP)/hardware/led
VPATH			+= $(TOP)/hardware/button
VPATH			+= $(TOP)/system

#设置自定义源文件目录
# APP_DIR			= $(TOP)/app
# HARD_DIR		= $(TOP)/hardware

#设置中间目标文件目录
OBJ_DIR			= $(TOP)/obj
#设置编译生成结果文件夹
BUILD_DIR		= $(TOP)/build
#设定头文件包含目录
INC_FLAGS 		+= -I $(TOP)/core
INC_FLAGS 		+= -I $(TOP)/core/cmsis
INC_FLAGS		+= -I $(TOP)/system
INC_FLAGS		+= -I $(TOP)/user
INC_FLAGS 		+= -I $(TOP)/core/cmsis/GD/GD32F10x/Include
INC_FLAGS 		+= -I $(TOP)/core/gd32f10x_standard_peripheral/Include
INC_FLAGS 		+= -I $(TOP)/hardware/button
INC_FLAGS 		+= -I $(TOP)/hardware/led
# INC_FLAGS 		+= -I $(TOP)/hardware/uart

#编译选项
CFLAGS 			+= -W -Wall -g -mcpu=cortex-m3 -mthumb -O2 -std=gnu11
CFLAGS 			+= -D GD32F10X_HD -D USE_STDPERIPH_DRIVER

#链接选项
LFLAGS 			+= -mthumb -mcpu=cortex-m3 -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs 
LFLAGS 			+= -specs=nosys.specs -static -Wl,-cref,-u,Reset_Handler -Wl,-Map=manual_board_gd32.map -Wl,--gc-sections 
LFLAGS 			+= -Wl,--defsym=malloc_getpagesize_P=0x80

#链接启动文件和链接脚本
LFLAGS			+= $(TOP)/core/cmsis/GD/GD32F10x/Source/GCC/startup_gd32f10x_hd.S
LFLAGS			+= -T $(TOP)/core/gd32f10x_lds/gd32f10x_flash.ld

#固定源文件添加
C_SRC			+= $(shell find $(TOP)/core/cmsis/GD/GD32F10x/Source  -name '*.$(EXT)')
C_SRC			+= $(shell find $(TOP)/core/gd32f10x_standard_peripheral/Source  -name '*.$(EXT)')
C_SRC			+= $(shell find $(TOP)/system  -name '*.$(EXT)')
C_SRC			+= $(shell find $(TOP)/user  -name '*.$(EXT)')
C_SRC			+= $(shell find $(TOP)/hardware/button  -name '*.$(EXT)')
C_SRC			+= $(shell find $(TOP)/hardware/led  -name '*.$(EXT)')
# C_SRC			+= $(shell find $(TOP)/hardware/uart  -name '*.$(EXT)')
#自定义源文件添加
# C_SRC			+= $(HARD_DIR)/LED/led.c

#中间目标文件
#C_OBJ			+= $(C_SRC:%.$(EXT)=%.o)
C_SRC_NODIR		= $(notdir $(C_SRC))
C_OBJ 			= $(patsubst %.$(EXT), $(OBJ_DIR)/%.o,$(C_SRC_NODIR))

#依赖文件
C_DEP			= $(patsubst %.$(EXT), $(OBJ_DIR)/%.d,$(C_SRC_NODIR))

.PHONY: all clean rebuild upload test ctags

all:$(C_OBJ)
	@echo "linking object to $(BUILD_DIR)/$(TARGET).elf"
	@$(CC) $(C_OBJ) -o $(BUILD_DIR)/$(TARGET).elf $(LFLAGS)
	@$(ARMSIZE) $(BUILD_DIR)/$(TARGET).elf
	@echo "create $(BUILD_DIR)/$(TARGET).hex from $(BUILD_DIR)/$(TARGET).elf"
	@$(OBJCOPY) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex -Oihex
	@$(ARMSIZE) $(BUILD_DIR)/$(TARGET).hex
#$(OBJCOPY) $(TARGET).elf  $(TARGET).bin -Obinary 

#静态模式
#$(C_OBJ):%.o:%.$(EXT)
#	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o:%.$(EXT)
	@mkdir -p obj
	@echo "building $<"
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) -o $@ $<

-include $(C_DEP)
$(OBJ_DIR)/%.d:%.$(EXT)
	@mkdir -p obj
	@echo "making $@"
	@set -e;rm -f $@;$(CC) -MM $(CFLAGS) $(INC_FLAGS) $< > $@.$$$$;sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $(OBJ_DIR)/\1.d:,g' < $@.$$$$ > $@;rm -f $@.$$$$

clean:
	-rm -f $(OBJ_DIR)/*
	-rm -f $(shell find ./ -name '*.map')
	-rm -f $(shell find ./ -name '*.elf')
	-rm -f $(shell find ./ -name '*.bin')
	-rm -f $(shell find ./ -name '*.hex')

rebuild: clean all

test:
	@echo "Test !"

ctags:
	@ctags -R *

download:
	openocd -f $(INTERFACE_CFG) -f $(TARGET_CFG) -c init -c halt -c "flash write_image erase $(PWD)/build/$(TARGET).hex" -c reset -c shutdown
