/*****************************************************************************
* Filename:          C:\Users\CJRipa\Pictures\Proyecto\PracticasSE/drivers/banner_v1_00_a/src/banner.h
* Version:           1.00.a
* Description:       banner Driver Header File
* Date:              Tue Jan 31 18:49:36 2023 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef BANNER_H
#define BANNER_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 */
#define BANNER_USER_SLV_SPACE_OFFSET (0x00000000)

/**
 * Read Packet FIFO Register/Data Space Offsets
 * -- RDFIFO_RST  : read packet fifo reset register
 * -- RDFIFO_SR   : read packet fifo status register
 * -- RDFIFO_DATA : read packet fifo data
 */
#define BANNER_RDFIFO_REG_SPACE_OFFSET (0x00000100)
#define BANNER_RDFIFO_RST_OFFSET (BANNER_RDFIFO_REG_SPACE_OFFSET + 0x00000000)
#define BANNER_RDFIFO_SR_OFFSET (BANNER_RDFIFO_REG_SPACE_OFFSET + 0x00000004)
#define BANNER_RDFIFO_DATA_SPACE_OFFSET (0x00000200)
#define BANNER_RDFIFO_DATA_OFFSET (BANNER_RDFIFO_DATA_SPACE_OFFSET + 0x00000000)

/**
 * Read Packet FIFO Masks
 * -- RDFIFO_EMPTY_MASK : read packet fifo empty condition
 * -- RDFIFO_AE_MASK    : read packet fifo almost empty condition
 * -- RDFIFO_DL_MASK    : read packet fifo deadlock condition
 * -- RDFIFO_SCL_MASK   : read packet fifo occupancy scaling enabled
 * -- RDFIFO_WIDTH_MASK : read packet fifo encoded data port width
 * -- RDFIFO_OCC_MASK   : read packet fifo occupancy
 * -- RDFIFO_RESET      : read packet fifo reset
 */
#define RDFIFO_EMPTY_MASK (0x80000000UL)
#define RDFIFO_AE_MASK (0x40000000UL)
#define RDFIFO_DL_MASK (0x20000000UL)
#define RDFIFO_SCL_MASK (0x10000000UL)
#define RDFIFO_WIDTH_MASK (0x0E000000UL)
#define RDFIFO_OCC_MASK (0x01FFFFFFUL)
#define RDFIFO_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a BANNER register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the BANNER device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void BANNER_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define BANNER_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a BANNER register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the BANNER device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 BANNER_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define BANNER_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Reset read packet FIFO of BANNER to its initial state.
 *
 * @param   BaseAddress is the base address of the BANNER device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void BANNER_mResetReadFIFO(Xuint32 BaseAddress)
 *
 */
#define BANNER_mResetReadFIFO(BaseAddress) \
 	Xil_Out32((BaseAddress)+(BANNER_RDFIFO_RST_OFFSET), RDFIFO_RESET)

/**
 *
 * Check status of BANNER read packet FIFO module.
 *
 * @param   BaseAddress is the base address of the BANNER device.
 *
 * @return  Status is the result of status checking.
 *
 * @note
 * C-style signature:
 * 	bool BANNER_mReadFIFOEmpty(Xuint32 BaseAddress)
 * 	Xuint32 BANNER_mReadFIFOOccupancy(Xuint32 BaseAddress)
 *
 */
#define BANNER_mReadFIFOEmpty(BaseAddress) \
 	((Xil_In32((BaseAddress)+(BANNER_RDFIFO_SR_OFFSET)) & RDFIFO_EMPTY_MASK) == RDFIFO_EMPTY_MASK)
#define BANNER_mReadFIFOOccupancy(BaseAddress) \
 	(Xil_In32((BaseAddress)+(BANNER_RDFIFO_SR_OFFSET)) & RDFIFO_OCC_MASK)

/**
 *
 * Read 32 bit data from BANNER read packet FIFO module.
 *
 * @param   BaseAddress is the base address of the BANNER device.
 * @param   DataOffset is the offset from the data port to read from.
 *
 * @return  Data is the data from the read packet FIFO.
 *
 * @note
 * C-style signature:
 * 	Xuint32 BANNER_mReadFromFIFO(Xuint32 BaseAddress, unsigned DataOffset)
 *
 */
#define BANNER_mReadFromFIFO(BaseAddress, DataOffset) \
 	Xil_In32((BaseAddress) + (BANNER_RDFIFO_DATA_OFFSET) + (DataOffset))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the BANNER instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus BANNER_SelfTest(void * baseaddr_p);

#endif /** BANNER_H */
