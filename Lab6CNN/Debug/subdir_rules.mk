################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
cnn.obj: ../cnn.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/grlib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/ipclite/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/nandlib/include" --gcc --define=omapl138 --define=lcdkOMAPL138 --define=DMA_MODE --diag_warning=225 --preproc_with_compile --preproc_dependency="cnn.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

exit.obj: ../exit.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/grlib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/ipclite/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/nandlib/include" --gcc --define=omapl138 --define=lcdkOMAPL138 --define=DMA_MODE --diag_warning=225 --preproc_with_compile --preproc_dependency="exit.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fat_usbmsc.obj: ../fat_usbmsc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/grlib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/ipclite/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/nandlib/include" --gcc --define=omapl138 --define=lcdkOMAPL138 --define=DMA_MODE --diag_warning=225 --preproc_with_compile --preproc_dependency="fat_usbmsc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ff.obj: ../ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/grlib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/ipclite/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/nandlib/include" --gcc --define=omapl138 --define=lcdkOMAPL138 --define=DMA_MODE --diag_warning=225 --preproc_with_compile --preproc_dependency="ff.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main_cnn.obj: ../main_cnn.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/grlib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/ipclite/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/nandlib/include" --gcc --define=omapl138 --define=lcdkOMAPL138 --define=DMA_MODE --diag_warning=225 --preproc_with_compile --preproc_dependency="main_cnn.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


