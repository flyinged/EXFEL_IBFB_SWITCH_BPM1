#################################################################
# Makefile generated by Xilinx Platform Studio 
# Project:C:\temp\G\GPAC\Board\GPAC2_1\BPM_FPGA\EXFEL_IBFB_SWITCH_BPM1\system.xmp
#
# WARNING : This file will be re-generated every time a command
# to run a make target is invoked. So, any changes made to this  
# file manually, will be lost when make is invoked next. 
#################################################################

SHELL = CMD

XILINX_EDK_DIR = C:/Xilinx/14.7/ISE_DS/EDK

SYSTEM = system

MHSFILE = system.mhs

FPGA_ARCH = virtex5

DEVICE = xc5vfx70tff1136-2

INTSTYLE = default

XPS_HDL_LANG = vhdl
GLOBAL_SEARCHPATHOPT =  -lp C:/temp/G/GPAC/Lib -lp C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw
PROJECT_SEARCHPATHOPT = 

SEARCHPATHOPT = $(PROJECT_SEARCHPATHOPT) $(GLOBAL_SEARCHPATHOPT)

SUBMODULE_OPT = 

PLATGEN_OPTIONS = -p $(DEVICE) -lang $(XPS_HDL_LANG) -intstyle $(INTSTYLE) $(SEARCHPATHOPT) $(SUBMODULE_OPT) -msg __xps/ise/xmsgprops.lst

OBSERVE_PAR_OPTIONS = -error yes

MICROBLAZE_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/microblaze/mb_bootloop.elf
MICROBLAZE_BOOTLOOP_LE = $(XILINX_EDK_DIR)/sw/lib/microblaze/mb_bootloop_le.elf
PPC405_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/ppc405/ppc_bootloop.elf
PPC440_BOOTLOOP = $(XILINX_EDK_DIR)/sw/lib/ppc440/ppc440_bootloop.elf
BOOTLOOP_DIR = bootloops

PPC440_INST_BOOTLOOP = $(BOOTLOOP_DIR)/ppc440_inst.elf

BRAMINIT_ELF_IMP_FILES = $(PPC440_INST_BOOTLOOP)
BRAMINIT_ELF_IMP_FILE_ARGS = -pe ppc440_inst $(PPC440_INST_BOOTLOOP)

BRAMINIT_ELF_SIM_FILES = $(PPC440_INST_BOOTLOOP)
BRAMINIT_ELF_SIM_FILE_ARGS = -pe ppc440_inst $(PPC440_INST_BOOTLOOP)

SIM_CMD = vsim

BEHAVIORAL_SIM_SCRIPT = simulation/behavioral/$(SYSTEM)_setup.do

STRUCTURAL_SIM_SCRIPT = simulation/structural/$(SYSTEM)_setup.do

TIMING_SIM_SCRIPT = simulation/timing/$(SYSTEM)_setup.do

DEFAULT_SIM_SCRIPT = $(BEHAVIORAL_SIM_SCRIPT)

SIMGEN_OPTIONS = -p $(DEVICE) -lang $(XPS_HDL_LANG) -intstyle $(INTSTYLE) $(SEARCHPATHOPT) $(BRAMINIT_ELF_SIM_FILE_ARGS) -msg __xps/ise/xmsgprops.lst -s mgm -X C:/temp/G/GPAC/Board/GPAC2_1/BPM_FPGA/EXFEL_IBFB_SWITCH_BPM1/


CORE_STATE_DEVELOPMENT_FILES = C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/netlist/v5_fifo_256x6.ngc \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/xfel_tim_bpm_mem_v1_00_a/netlist/v5_mem_dp_9x2048.ngc \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/fpga_technology_package_virtex5_v1_00_a/hdl/vhdl/fpga_technology_package_virtex5.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/hdl/vhdl/rx_sync.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/hdl/vhdl/virtex5_gtx_package.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/hdl/vhdl/pkg_psi_ms_plb46.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/hdl/vhdl/pkg_psi_plbovergtx.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/psi_plbovergtx_v2_03_a/hdl/vhdl/psi_plbovergtx.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/family.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/family_support.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/coregen_comp_defs.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/common_types_pkg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/proc_common_pkg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/conv_funs_pkg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ipif_pkg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/async_fifo_fg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/sync_fifo_fg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/basic_sfifo_fg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/blk_mem_gen_wrapper.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/addsub.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/counter_bit.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/counter.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/direct_path_cntr.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/direct_path_cntr_ai.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/down_counter.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/eval_timer.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/inferred_lut4.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ipif_steer.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ipif_steer128.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ipif_mirror128.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ld_arith_reg.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/ld_arith_reg2.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/mux_onehot.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_bits.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_muxcy.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_gate.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_gate128.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_adder_bit.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_adder.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_counter_bit.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_counter.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_counter_top.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_occ_counter.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_occ_counter_top.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pf_dpram_select.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pselect.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pselect_mask.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl16_fifo.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo2.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo3.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo_rbu.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/valid_be.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_with_enable_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/muxf_struct_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/cntr_incr_decr_addn_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/dynshreg_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/dynshreg_i_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/mux_onehot_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo_rbu_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/srl_fifo_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/compare_vectors_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/pselect_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/counter_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_muxcy_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/or_gate_f.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/proc_common_v3_00_a/hdl/vhdl/soft_reset.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_single_v1_01_a/hdl/vhdl/plb_address_decoder.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_single_v1_01_a/hdl/vhdl/plb_slave_attachment.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_single_v1_01_a/hdl/vhdl/plbv46_slave_single.vhd \
pcores/gpac2_bpm_service_v1_00_a/hdl/vhdl/gpac2_bpm_service.vhd \
pcores/gpac2_bpm_service_v1_00_a/hdl/vhdl/user_logic.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/flex_addr_cntr.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/addr_reg_cntr_brst_flex.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/plb_address_decoder.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/burst_support.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/wr_buffer.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/be_reset_gen.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/plb_slave_attachment.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/data_mirror_128.vhd \
C:/Xilinx/14.7/ISE_DS/EDK/hw/XilinxProcessorIPLib/pcores/plbv46_slave_burst_v1_01_a/hdl/vhdl/plbv46_slave_burst.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/rx_sync.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/pkg_crc.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/ram_infer.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/virtex5_gtx_package.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/ibfb_comm_package.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_common_v1_00_b/hdl/vhdl/pkg_ibfb_timing.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_switch_v2_00_b/hdl/vhdl/user_logic.vhd \
C:/temp/G/XFEL/14_Firmware/22_Library/EDKLib/hw/PSI/pcores/ibfb_switch_v2_00_b/hdl/vhdl/ibfb_switch.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/xfel_tim_bpm_mem_v1_00_a/hdl/vhdl/user_logic.vhd \
C:/temp/G/GPAC/Lib/EDK_Lib/pcores/xfel_tim_bpm_mem_v1_00_a/hdl/vhdl/xfel_tim_bpm_mem.vhd

WRAPPER_NGC_FILES = implementation/system_clock_generator_0_wrapper.ngc \
implementation/system_idelay_ctrl_0_wrapper.ngc \
implementation/system_reset_inst_wrapper.ngc \
implementation/system_jtagppc_cntlr_inst_wrapper.ngc \
implementation/system_ppc440_inst_wrapper.ngc \
implementation/system_apu_fpu_virtex5_0_wrapper.ngc \
implementation/system_fcb_v20_0_wrapper.ngc \
implementation/system_plb_inst_wrapper.ngc \
implementation/system_ddr2_sdram_w1d32m72r8a_5a_wrapper.ngc \
implementation/system_intc_inst_wrapper.ngc \
implementation/system_ibfb_tasks_wrapper.ngc \
implementation/system_bram1_cntlr_inst_wrapper.ngc \
implementation/system_bram1_inst_wrapper.ngc \
implementation/system_uart_inst_wrapper.ngc \
implementation/system_plbovergtx_sys_wrapper.ngc \
implementation/system_ibfb_func_ctrl_wrapper.ngc \
implementation/system_bpm_service_wrapper.ngc \
implementation/system_plboverlvds_bp_wrapper.ngc \
implementation/system_qdr2_splb_wrapper.ngc \
implementation/system_mgt112_not_used_wrapper.ngc \
implementation/system_mgt118_not_used_wrapper.ngc \
implementation/system_ibfb_switch_0_wrapper.ngc \
implementation/system_gpac_eeprom_0_wrapper.ngc \
implementation/system_xfel_tim_sys_rx_wrapper.ngc \
implementation/system_chipscope_icon_0_wrapper.ngc \
implementation/system_ila_router_wrapper.ngc

POSTSYN_NETLIST = implementation/$(SYSTEM).ngc

SYSTEM_BIT = implementation/$(SYSTEM).bit

DOWNLOAD_BIT = implementation/download.bit

SYSTEM_ACE = implementation/$(SYSTEM).ace

UCF_FILE = data\system.ucf

BMM_FILE = implementation/$(SYSTEM).bmm

BITGEN_UT_FILE = etc/bitgen.ut

XFLOW_OPT_FILE = etc/fast_runtime.opt
XFLOW_DEPENDENCY = __xps/xpsxflow.opt $(XFLOW_OPT_FILE)

XPLORER_DEPENDENCY = __xps/xplorer.opt
XPLORER_OPTIONS = -p $(DEVICE) -uc $(SYSTEM).ucf -bm $(SYSTEM).bmm -max_runs 7

FPGA_IMP_DEPENDENCY = $(BMM_FILE) $(POSTSYN_NETLIST) $(UCF_FILE) $(XFLOW_DEPENDENCY)

SDK_EXPORT_DIR = SDK_Export\hw
SYSTEM_HW_HANDOFF = $(SDK_EXPORT_DIR)/$(SYSTEM).xml
SYSTEM_HW_HANDOFF_BIT = $(SDK_EXPORT_DIR)/$(SYSTEM).bit
SYSTEM_HW_HANDOFF_BMM = $(SDK_EXPORT_DIR)/$(SYSTEM)_bd.bmm
SYSTEM_HW_HANDOFF_DEP = $(SYSTEM_HW_HANDOFF) $(SYSTEM_HW_HANDOFF_BIT) $(SYSTEM_HW_HANDOFF_BMM)
