###################################################################
##
## Copyright(C) 2003-2006 by Xilinx, Inc. All rights reserved.
##
## chipscope_vio
##
###################################################################

#
# ELABORATE_PROC
#


proc date_generate { mhsinst } {

   puts "Compilation date and time is set to:"

   set date_raw     [clock seconds]

   set c_date [clock format $date_raw -format %Y]
   scan $c_date "%d" c_date_int 
   set parm_handle [xget_hw_parameter_handle $mhsinst "C_DATE_YEAR"]
   xset_hw_parameter_value $parm_handle [expr $c_date_int]
   puts "C_DATE_YEAR   : $c_date_int"

   set c_date [clock format $date_raw -format %m]
   scan $c_date "%d" c_date_int 
   set parm_handle [xget_hw_parameter_handle $mhsinst "C_DATE_MONTH"]
   xset_hw_parameter_value $parm_handle [expr $c_date_int]
   puts "C_DATE_MONTH  : $c_date_int"

   set c_date [clock format $date_raw -format %e]
   scan $c_date "%d" c_date_int 
   set parm_handle [xget_hw_parameter_handle $mhsinst "C_DATE_DAY"]
   xset_hw_parameter_value $parm_handle [expr $c_date_int]
   puts "C_DATE_DAY    : $c_date_int"

   set c_date [clock format $date_raw -format %k]
   scan $c_date "%d" c_date_int 
   set parm_handle [xget_hw_parameter_handle $mhsinst "C_DATE_HOUR"]
   xset_hw_parameter_value $parm_handle [expr $c_date_int]
   puts "C_DATE_HOUR   : $c_date_int"

   set c_date [clock format $date_raw -format %M]
   scan $c_date "%d" c_date_int 
   set parm_handle [xget_hw_parameter_handle $mhsinst "C_DATE_MINUTE"]
   xset_hw_parameter_value $parm_handle [expr $c_date_int]
   puts "C_DATE_MINUTE : $c_date_int"

   return
}
