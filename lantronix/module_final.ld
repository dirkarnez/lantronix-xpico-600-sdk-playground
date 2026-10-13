/*
** Copyright ©2015-2024, Lantronix, Inc. All Rights Reserved.
** By using this software, you are agreeing to the terms of the Software
** Development Kit (SDK) License Agreement included in the distribution package
** for this software (the “License Agreement”).
** Under the License Agreement, this software may be used solely to create
** custom applications for use on the Lantronix xPico Wi-Fi product.
** THIS SOFTWARE AND ANY ACCOMPANYING DOCUMENTATION IS PROVIDED "AS IS".
** LANTRONIX SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS
** FOR A PARTICULAR PURPOSE.
** LANTRONIX HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
** ENHANCEMENTS, OR MODIFICATIONS TO THIS SOFTWARE.
** IN NO EVENT SHALL LANTRONIX BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
** SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
** ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
** LANTRONIX HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

SECTIONS
{
    .text :
    {
        *(.text_front)
        *(.text_rear)
        . = ALIGN(8);
    }=0xffffffff

    .data : AT( ADDR(.text) + SIZEOF(.text) )
    {
        *(.data)
        . = ALIGN(8);
        ltrx_linker_module_flash_end = . - ADDR(.data) + LOADADDR(.data);
    }=0xffffffff

    .bss :
    {
        *(.bss)
        *(COMMON)
        . = ALIGN(8);
        ltrx_linker_module_ram_end = .;
    }

}

ltrx_linker_code_size = SIZEOF(.text);
ltrx_linker_data_size = SIZEOF(.data);
ltrx_linker_bss_size = SIZEOF(.bss);
