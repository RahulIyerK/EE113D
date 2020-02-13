################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
NeuralNet/neuralNet.obj: ../NeuralNet/neuralNet.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/L138_support" --include_path="C:/ti/OMAP-L138_GEL_BSL_Files/bsl/inc" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="C:/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="C:/Users/ECE113DWS20/Documents/More_CCS_Stuff/EE113D/Lab5/NeuralNet" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="NeuralNet/neuralNet.pp" --obj_directory="NeuralNet" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


