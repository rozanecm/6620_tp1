#include <mips/regdef.h>

.globl mcd
.globl mcm


.text
.abicalls
.align 2
.ent mcm


mcm:

    #define mcm_frame_size 32
    #define mcm_frame_ra 24
    #define mcm_frame_fp 20
    #define mcm_frame_gp 16
    #define mcm_frame_2arg 36
    #define mcm_frame_1arg 32
    
    .frame $fp, mcm_frame_size, ra
    /*CREATE STACK FRAME*/
    subu sp, sp, mcm_frame_size
    .cprestore 16
    sw gp, mcm_frame_gp(sp)
    sw $fp, mcm_frame_fp(sp)
    sw ra, mcm_frame_ra(sp)
    move  $fp, sp /* frame pointer at the bottom */
      
    sw a0, mcm_frame_1arg($fp) /*save first argument (int a)*/
    sw a1, mcm_frame_2arg($fp) /*save second argument (int b)*/

    lw t3, mcm_frame_1arg($fp) /* use temporary for a0 value */
    lw t4, mcm_frame_2arg($fp) /* use temporary for a1 value */
   
    mul t3, t3, t4 /* (a * b) */
    
    la t5, mcd /* load address of mcd function */
    jalr t5     /* jump and link to mcd */
    
    div t3, t3, v0 /* (a * b) / mcd(a, b); */

    move v0, t3 /* set result */


    /* PREPARE TO DELETE STACK */
    lw gp, mcm_frame_gp(sp)
    lw $fp, mcm_frame_fp(sp)
    lw ra, mcm_frame_ra(sp)
    addu sp, sp, mcm_frame_size
    jr ra
    
.end mcm
   
.text
.abicalls
.align 2
.ent mcd

mcd:

    #define mcd_frame_size 32
    #define mcd_frame_ra 24
    #define mcd_frame_fp 20
    #define mcd_frame_gp 16
    #define mcd_frame_2arg 36
    #define mcd_frame_1arg 32
    
    .frame $fp, mcd_frame_size, ra
    /*CREATE STACK*/
    subu sp, sp, mcd_frame_size
    .cprestore 16
    sw gp, mcd_frame_gp(sp)
    sw $fp, mcd_frame_fp(sp)
    sw ra, mcd_frame_ra(sp)
    move  $fp, sp /* From here, we use frame pointer */
 
    sw a0, mcd_frame_1arg($fp) /*save first argument (int a)*/
    sw a1, mcd_frame_2arg($fp) /*save second argument (int b)*/

    beq a1, zero, return_a /*if b == 0 then return a*/

    lw t0, mcd_frame_2arg($fp) /* use temporary for a1 value */
    lw t1, mcd_frame_1arg($fp) /* use temporary for a0 value */

    move a0, t0 /* use b as first argument */
    remu a1, t1, t0 /* a % b, used as second argument*/
    
    jal mcd

return_a: 
    move v0, a0

    /* PREPARE TO DELETE STACK */
    lw gp, mcd_frame_gp(sp)
    lw $fp, mcd_frame_fp(sp)
    lw ra, mcd_frame_ra(sp)
    addu sp, sp, mcd_frame_size
    jr ra


.end mcd

    
    
