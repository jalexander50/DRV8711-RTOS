################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
MSP_EXP432P401R.obj: ../MSP_EXP432P401R.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/ccs_base/arm/include" --include_path="C:/ti/ccsv6/ccs_base/arm/include/CMSIS" --include_path="C:/Users/jalex_000/workspace_v6_2/DRV8711-RTOS" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS/include" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="MSP_EXP432P401R.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/ccs_base/arm/include" --include_path="C:/ti/ccsv6/ccs_base/arm/include/CMSIS" --include_path="C:/Users/jalex_000/workspace_v6_2/DRV8711-RTOS" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc" --include_path="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS/include" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-1345253055: ../main.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/tirex-content/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/packages;C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages;C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/tidrivers_msp43x_2_20_00_08/packages;C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/uia_2_00_06_52/packages;C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/packages;C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/packages;C:/ti/msp/MSP432Ware_3_50_00_02/driverlib;C:/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r release -c "C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"C:/ti/ccsv6/ccs_base/arm/include\" --include_path=\"C:/ti/ccsv6/ccs_base/arm/include/CMSIS\" --include_path=\"C:/Users/jalex_000/workspace_v6_2/DRV8711-RTOS\" --include_path=\"C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc/CMSIS\" --include_path=\"C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/inc\" --include_path=\"C:/ti/tirex-content/tirtos_msp43x_2_20_00_06/products/msp432_driverlib_3_21_00_05/driverlib/MSP432P4xx\" --include_path=\"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.4.LTS/include\" --advice:power_severity=suppress --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --define=MSP432WARE --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-1345253055
configPkg/compiler.opt: build-1345253055
configPkg/: build-1345253055


