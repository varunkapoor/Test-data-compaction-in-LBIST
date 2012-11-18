# Initial Configuration
set_messages -double_slash -log ./LOGS/Tmax.log -append
# Front End Kit settings
report_version –full
build -force
# Remove all netlist and library modules
read_netlist -delete
# Read Libraries
read_netlist /sw/unicad/CORE65LPSVT/5.1/behaviour/verilog/CORE65LPSVT.v -library
# Read the Top Level netlist
read_netlist /data/rdmst8/DFT_REF_DESIGNS/LINFLEX/NETLIST/linflex.v
set_build -nodelete_unused_gates
set_build -merge noequivalent_dlat_dff
run_build_model linflex -remove_pio_pull
# Scan-enable inactive (capture phase)
add_pi_constraints 0 SCAN_EN
# Disable active low asynchronous reset (capture phase)
add_pi_constraints 1 presetn
# Slow bidirectional pads management
add_slow_bidis -all
# Mask all output port
add_po_masks -all
# Simulation setting
set_simulation -nopipeline_cells
set_simulation -bidi_fill
set_simulation -xclock_gives_xout
set_simulation -xfill_out_of_range_write
# Read protocol file
set_drc /data/rdmst8/DFT_REF_DESIGNS/LINFLEX/SYNTHESIS/linflex.spf
# DRC setting
set_drc -nodslave_remodel –noshadows
set_drc -allow_unstable_set_resets
set_drc -store_setup
set_drc -low_power
# DRC
run_drc
# Set fault model
set_faults -noequiv_code -model stuck -pt_credit 0 -summary verbose -report uncollapsed -
atpg_effectiveness -fault_coverage
# Add fault
remove_faults –all
remove_nofaults -all
read_faults ./FAULTS/Faults -force_retain_code
reset_au_faults
set_patterns -external ./PATTERNS/x_filled_patt.stil –sensitive
run_fault_sim -ndetects 1
write_faults ./FAULTS/Faults -all –replace
set_patterns -internal
# ATPG setting
set_atpg -fill X
set_atpg –verbose
set_atpg -chain_test off
set_atpg -merge off
set_patterns -histogram_summary -load_summary
run_atpg
# Save patterns
write_patterns ./PATTERNS/Patterns.serial_mod.stil -format stil -serial -internal –replace