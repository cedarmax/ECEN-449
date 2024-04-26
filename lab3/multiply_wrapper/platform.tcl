# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/ugrads/c/cedarmaxwell/Documents/ECEN449/lab3/multiply_wrapper/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/ugrads/c/cedarmaxwell/Documents/ECEN449/lab3/multiply_wrapper/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {multiply_wrapper}\
-hw {/home/ugrads/c/cedarmaxwell/Documents/ECEN449/lab3/multiply_wrapper.xsa}\
-out {/home/ugrads/c/cedarmaxwell/Documents/ECEN449/lab3}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {multiply_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
