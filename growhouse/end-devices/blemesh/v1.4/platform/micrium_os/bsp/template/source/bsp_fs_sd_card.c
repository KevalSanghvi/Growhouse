/***************************************************************************//**
 * @file
 * @brief Sdmmc Card (Card Mode) BSP - Template
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/********************************************************************************************************
 ********************************************************************************************************
 *                                     DEPENDENCIES & AVAIL CHECK(S)
 ********************************************************************************************************
 *******************************************************************************************************/

#define    FS_DEV_SD_CARD_BSP_MODULE
#include  <common/include/rtos_path.h>
#include  <rtos_description.h>

#if  defined(RTOS_MODULE_FS_AVAIL) && defined(RTOS_MODULE_FS_STORAGE_SD_CARD_AVAIL)

/********************************************************************************************************
 ********************************************************************************************************
 *                                            INCLUDE FILES
 ********************************************************************************************************
 * Note(s) : (1) The kal_priv.h file is included only to be used by this file. Its content should remain
 *               private to rtos and not be used in an application's context.
 ********************************************************************************************************
 *******************************************************************************************************/

#include  <fs/include/fs_sd_card.h>

#include  <common/source/kal/kal_priv.h>
#include  <common/include/lib_def.h>
#include  <common/include/lib_utils.h>
#include  <common/include/rtos_utils.h>

/********************************************************************************************************
 ********************************************************************************************************
 *                                            LOCAL DEFINES
 *
 * Note(s) : (1) The SDMMC requires a clock of 48MHz or less to work. This clock is generated by the
 *               Reset and Clock Control (RCC) peripheral.
 *
 ********************************************************************************************************
 *******************************************************************************************************/

//                                                                 ----------------- INTERRUPT DEFINES ----------------
#define  SD_CARD_INT_ID_SDIO                        BSP_INT_ID_SDMMC1

//                                                                 ----------------- FREQUENCY DEFINES ----------------
#define  SD_CARD_SDIOCLK_CLK_FREQ_HZ                48000000uL  // See Note #1.

//                                                                 ---------------- TIME-BASED DEFINES ----------------
#define  SD_CARD_WAIT_TIMEOUT_MS                    500u

/********************************************************************************************************
 *                                          REGISTER DEFINES
 *******************************************************************************************************/

/********************************************************************************************************
 *                                        REGISTER BIT DEFINES
 *******************************************************************************************************/

/********************************************************************************************************
 ********************************************************************************************************
 *                                          LOCAL DATA TYPES
 ********************************************************************************************************
 *******************************************************************************************************/

typedef struct bsp_fs_sd_card_data {
  FS_DEV_SD_CARD_ERR BSP_Err;                                   // Error status that can be set by interrupt handler.
  KAL_SEM_HANDLE     OS_Sem;                                    // Semaphore used for data transfer in interrupt mode.
  KAL_LOCK_HANDLE    OS_LockHandle;                             // Lock to protect SD Card bus from multiple accesses.
} BSP_FS_SD_CARD_DATA;

/********************************************************************************************************
 ********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 ********************************************************************************************************
 *******************************************************************************************************/

static BSP_FS_SD_CARD_DATA BSP_FS_SD_Card_Data = {
  .BSP_Err = FS_DEV_SD_CARD_ERR_NONE,
  .OS_Sem = KAL_SEM_HANDLE_NULL,
  .OS_LockHandle = KAL_LOCK_HANDLE_NULL
};

/********************************************************************************************************
 ********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 ********************************************************************************************************
 *******************************************************************************************************/

//                                                                 ---------- FILE SYSTEM SD CARD FUNCTIONS -----------
static void *BSP_FS_SD_Card_Add(RTOS_ERR *p_err);

static CPU_BOOLEAN BSP_FS_SD_Card_Open(void);

static void BSP_FS_SD_Card_Close(void);

static void BSP_FS_SD_Card_Lock(void);

static void BSP_FS_SD_Card_Unlock(void);

static void BSP_FS_SD_Card_CmdStart(FS_DEV_SD_CARD_CMD *p_cmd,
                                    void               *p_data,
                                    FS_DEV_SD_CARD_ERR *p_err);

static void BSP_FS_SD_Card_CmdEndWait(FS_DEV_SD_CARD_CMD *p_cmd,
                                      CPU_INT32U         *p_resp,
                                      FS_DEV_SD_CARD_ERR *p_err);

static void BSP_FS_SD_Card_CmdDataRd(FS_DEV_SD_CARD_CMD *p_cmd,
                                     void               *p_dest,
                                     FS_DEV_SD_CARD_ERR *p_err);

static void BSP_FS_SD_Card_CmdDataWr(FS_DEV_SD_CARD_CMD *p_cmd,
                                     void               *p_src,
                                     FS_DEV_SD_CARD_ERR *p_err);

static CPU_INT32U BSP_FS_SD_Card_BlkCntMaxGet(CPU_INT32U blk_size);

static CPU_INT08U BSP_FS_SD_Card_BusWidthMaxGet(void);

static void BSP_FS_SD_Card_BusWidthSet(CPU_INT08U width);

static void BSP_FS_SD_Card_ClkFreqSet(CPU_INT32U freq);

static void BSP_FS_SD_Card_TimeoutDataSet(CPU_INT32U to_clks);

static void BSP_FS_SD_Card_TimeoutRespSet(CPU_INT32U to_ms);
//                                                                 ---------------- INTERNAL FUNCTIONS ----------------
static void BSP_FS_SD_Card_ISR_Handler(void);

static const FS_SD_CARD_BSP_API BSP_FS_SD_Card_Template_BSP_API = {
  .Add = BSP_FS_SD_Card_Add,
  .Open = BSP_FS_SD_Card_Open,
  .Close = BSP_FS_SD_Card_Close,
  .Lock = BSP_FS_SD_Card_Lock,
  .Unlock = BSP_FS_SD_Card_Unlock,
  .CmdStart = BSP_FS_SD_Card_CmdStart,
  .CmdEndWait = BSP_FS_SD_Card_CmdEndWait,
  .CmdDataRd = BSP_FS_SD_Card_CmdDataRd,
  .CmdDataWr = BSP_FS_SD_Card_CmdDataWr,
  .BlkCntMaxGet = BSP_FS_SD_Card_BlkCntMaxGet,
  .BusWidthMaxGet = BSP_FS_SD_Card_BusWidthMaxGet,
  .BusWidthSet = BSP_FS_SD_Card_BusWidthSet,
  .ClkFreqSet = BSP_FS_SD_Card_ClkFreqSet,
  .TimeoutDataSet = BSP_FS_SD_Card_TimeoutDataSet,
  .TimeoutRespSet = BSP_FS_SD_Card_TimeoutRespSet
};

const FS_SD_CARD_HW_INFO BSP_FS_SD_Card_HwInfo = {              // SD Card HW info passed to FS_SD_CARD_HW_INFO_REG().
  .BspApiPtr = &BSP_FS_SD_Card_Template_BSP_API,
  .AlignReq = sizeof(CPU_ALIGN)
};

/********************************************************************************************************
 ********************************************************************************************************
 *                                    FILE SYSTEM SD CARD FUNCTIONS
 ********************************************************************************************************
 *******************************************************************************************************/

/********************************************************************************************************
 *                                          BSP_FS_SD_Card_Add()
 *
 * Description : Add SD/MMC card interface.
 *
 * Argument(s) : p_err       Pointer to variable that will receive the return error code
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void *BSP_FS_SD_Card_Add(RTOS_ERR *p_err)
{
  //                                                               TODO: Add instructions related to SD Card controller.

  RTOS_ERR_SET(*p_err, RTOS_ERR_NONE);
  return (DEF_NULL);
}

/********************************************************************************************************
 *                                         BSP_FS_SD_Card_Open()
 *
 * Description : Open (initialize) SD/MMC card interface.
 *
 * Argument(s) : None.
 *
 * Return(s)   : DEF_OK,   if interface was opened.
 *               DEF_FAIL, otherwise.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_SD_Card_Open(void)
{
  RTOS_ERR err;

  //                                                               Create semaphore used for data transfer completion.
  BSP_FS_SD_Card_Data.OS_Sem = KAL_SemCreate("BSP FS SD Card Sem", DEF_NULL, &err);
  if (RTOS_ERR_CODE_GET(err) != RTOS_ERR_NONE) {
    return (DEF_FAIL);
  }
  //                                                               Create lock to protect possibly shared SD card bus.
  BSP_FS_SD_Card_Data.OS_LockHandle = KAL_LockCreate("FS SD Card bus lock handle", DEF_NULL, &err);
  if (RTOS_ERR_CODE_GET(err) != RTOS_ERR_NONE) {
    return (DEF_FAIL);
  }

  //                                                               TODO: Add any other instructions to initialize SD Card controller such as interrupts, IO configuration, etc.

  return (DEF_OK);
}

/********************************************************************************************************
 *                                        BSP_FS_SD_Card_Close()
 *
 * Description : Close (unitialize) SD/MMC card interface.
 *
 * Argument(s) : None.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) This function will be called EVERY time the device is closed.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_Close(void)
{
  KAL_SemDel(BSP_FS_SD_Card_Data.OS_Sem);                       // Delete data transfer semaphore.
  KAL_LockDel(BSP_FS_SD_Card_Data.OS_LockHandle);               // Delete SD card bus protection lock.

  //                                                               TODO: Add any other instructions to unitialize SD Card controller...
  //                                                               ... It could be for example resetting some registers, disabling interrupts, etc.
}

/********************************************************************************************************
 *                                         BSP_FS_SD_Card_Lock()
 *
 * Description : Acquire SD/MMC card bus lock.
 *
 * Argument(s) : None.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) This function will be called before the SD/MMC driver begins to access the SD/MMC
 *                   card bus.  The application should NOT use the same bus to access another device until
 *                   the matching call to 'BSP_FS_SD_Card_Unlock()' has been made.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_Lock(void)
{
  RTOS_ERR err;

  KAL_LockAcquire(BSP_FS_SD_Card_Data.OS_LockHandle,
                  KAL_OPT_PEND_NONE,
                  KAL_TIMEOUT_INFINITE,
                  &err);
  APP_RTOS_ASSERT_CRITICAL(RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE,; );
}

/********************************************************************************************************
 *                                        BSP_FS_SD_Card_Unlock()
 *
 * Description : Release SD/MMC card bus lock.
 *
 * Argument(s) : None.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) 'BSP_FS_SD_Card_Lock()' will be called before the SD/MMC driver begins to access
 *                   the SD/MMC card bus.  The application should NOT use the same bus to access another
 *                   device until the matching call to this function has been made.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_Unlock(void)
{
  RTOS_ERR err;

  KAL_LockRelease(BSP_FS_SD_Card_Data.OS_LockHandle,
                  &err);
  APP_RTOS_ASSERT_CRITICAL(RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE,; );
}

/********************************************************************************************************
 *                                       BSP_FS_SD_Card_CmdStart()
 *
 * Description : Start a command.
 *
 * Argument(s) : p_cmd       Pointer to command to transmit (see Note #2).
 *
 *               p_data      Pointer to buffer address for DMA transfer (see Note #3).
 *
 *               p_err       Pointer to variable that will receive the return error code from this function :
 *
 *                               FS_DEV_SD_CARD_ERR_NONE       No error.
 *                               FS_DEV_SD_CARD_ERR_NO_CARD    No card present.
 *                               FS_DEV_SD_CARD_ERR_BUSY       Controller is busy.
 *                               FS_DEV_SD_CARD_ERR_UNKNOWN    Unknown or other error.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) The command start will be followed by zero, one or two additional BSP function calls,
 *                   depending on whether data should be transferred and on whether any errors occur.
 *
 *                   (a) 'BSP_FS_SD_Card_CmdStart()' starts execution of the command.  It may also set
 *                       up the DMA transfer (if necessary).
 *
 *                   (b) 'BSP_FS_SD_Card_CmdEndWait()' waits for the execution of the command to end,
 *                       getting the command response (if any).
 *
 *                   (c) If data should be transferred from the card to the host, 'BSP_FS_SD_Card_CmdDataRd()'
 *                       will read that data; if data should be transferred from the host to the card,
 *                       'BSP_FS_SD_Card_CmdDataWr()' will write that data.
 *
 *                   (d) If an error is returned at any point, the sequence will be aborted.
 *
 *               (2) The command 'p_cmd' has the following parameters :
 *
 *                   (a) 'p_cmd->Cmd' is the command index.
 *
 *                   (b) 'p_cmd->Arg' is the 32-bit argument (or 0 if there is no argument).
 *
 *                   (c) 'p_cmd->Flags' is a bit-mapped variable with zero or more command flags :
 *
 *                           FS_DEV_SD_CARD_CMD_FLAG_INIT          Initialization sequence before command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_BUSY          Busy signal expected after command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_CRC_VALID     CRC valid after command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_IX_VALID      Index valid after command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_OPEN_DRAIN    Command line is open drain.
 *                           FS_DEV_SD_CARD_CMD_FLAG_DATA_START    Data start command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_DATA_STOP     Data stop command.
 *                           FS_DEV_SD_CARD_CMD_FLAG_RESP          Response expected.
 *                           FS_DEV_SD_CARD_CMD_FLAG_RESP_LONG     Long response expected.
 *
 *                   (d) 'p_cmd->DataDir' indicates the direction of any data transfer that should follow
 *                       this command, if any :
 *
 *                           FS_DEV_SD_CARD_DATA_DIR_NONE            No data transfer.
 *                           FS_DEV_SD_CARD_DATA_DIR_HOST_TO_CARD    Transfer host-to-card (write).
 *                           FS_DEV_SD_CARD_DATA_DIR_CARD_TO_HOST    Transfer card-to-host (read).
 *
 *                   (e) 'p_cmd->DataType' indicates the type of the data transfer that should follow this
 *                       command, if any :
 *
 *                           FS_DEV_SD_CARD_DATA_TYPE_NONE            No data transfer.
 *                           FS_DEV_SD_CARD_DATA_TYPE_SINGLE_BLOCK    Single data block.
 *                           FS_DEV_SD_CARD_DATA_TYPE_MULTI_BLOCK     Multiple data blocks.
 *                           FS_DEV_SD_CARD_DATA_TYPE_STREAM          Stream data.
 *
 *                   (f) 'p_cmd->RespType' indicates the type of the response that should be expected from
 *                       this command :
 *
 *                           FS_DEV_SD_CARD_RESP_TYPE_NONE    No  response.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R1      R1  response: Normal Response Command.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R1B     R1b response.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R2      R2  response: CID, CSD Register.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R3      R3  response: OCR Register.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R4      R4  response: Fast I/O Response (MMC).
 *                           FS_DEV_SD_CARD_RESP_TYPE_R5      R5  response: Interrupt Request Response (MMC).
 *                           FS_DEV_SD_CARD_RESP_TYPE_R5B     R5B response.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R6      R6  response: Published RCA Response.
 *                           FS_DEV_SD_CARD_RESP_TYPE_R7      R7  response: Card Interface Condition.
 *
 *                   (g) 'p_cmd->BlkSize' and 'p_cmd->BlkCnt' are the block size and block count of the
 *                       data transfer that should follow this command, if any.
 *
 *               (3) The pointer to the data buffer that will receive the data transfer that should follow
 *                   this command is given so that a DMA transfer can be set up.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_CmdStart(FS_DEV_SD_CARD_CMD *p_cmd,
                                    void               *p_data,
                                    FS_DEV_SD_CARD_ERR *p_err)
{
  //                                                               TODO: Add instructions to setup and send the SD command to the SD Card.
  //                                                               You may setup and start a DMA transfer for the data phase if needed.

  PP_UNUSED_PARAM(p_cmd);
  PP_UNUSED_PARAM(p_data);

  *p_err = FS_DEV_SD_CARD_ERR_NONE;
}

/********************************************************************************************************
 *                                      BSP_FS_SD_Card_CmdEndWait()
 *
 * Description : Wait for command to end & get command response.
 *
 * Argument(s) : p_cmd       Pointer to command that is ending.
 *
 *               p_resp      Pointer to buffer that will receive command response, if any.
 *
 *               p_err       Pointer to variable that will receive the return error code from this function :
 *
 *                               FS_DEV_SD_CARD_ERR_NONE            No error.
 *                               FS_DEV_SD_CARD_ERR_NO_CARD         No card present.
 *                               FS_DEV_SD_CARD_ERR_UNKNOWN         Unknown or other error.
 *                               FS_DEV_SD_CARD_ERR_WAIT_TIMEOUT    Timeout in waiting for command response.
 *                               FS_DEV_SD_CARD_ERR_RESP_TIMEOUT    Timeout in receiving command response.
 *                               FS_DEV_SD_CARD_ERR_RESP_CHKSUM     Error in response checksum.
 *                               FS_DEV_SD_CARD_ERR_RESP_CMD_IX     Response command index error.
 *                               FS_DEV_SD_CARD_ERR_RESP_END_BIT    Response end bit error.
 *                               FS_DEV_SD_CARD_ERR_RESP            Other response error.
 *                               FS_DEV_SD_CARD_ERR_DATA            Other data err.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) This function will be called even if no response is expected from the command.
 *
 *               (2) This function will NOT be called if 'BSP_FS_SD_Card_CmdStart()' returns an error.
 *
 *               (3) (a) For a command with a normal response, a  4-byte response should be stored in
 *                       'p_resp'.
 *
 *                   (b) For a command with a long   response, a 16-byte response should be stored in
 *                       'p_resp'.  The first  4-byte word should hold bits 127..96 of the response.
 *                                  The second 4-byte word should hold bits  95..64 of the response.
 *                                  The third  4-byte word should hold bits  63..32 of the response.
 *                                  The fourth 4-byte word should hold bits  31.. 0 of the reponse.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_CmdEndWait(FS_DEV_SD_CARD_CMD *p_cmd,
                                      CPU_INT32U         *p_resp,
                                      FS_DEV_SD_CARD_ERR *p_err)
{
  RTOS_ERR err;

  //                                                               TODO: you may want to pend until the command phase completes or timeouts.
  KAL_SemPend(BSP_FS_SD_Card_Data.OS_Sem,
              KAL_OPT_PEND_NONE,
              0u,
              &err);
  if (RTOS_ERR_CODE_GET(err) != RTOS_ERR_NONE) {
    return;
  }

  //                                                               TODO: Add other instructions to process the response following the SD command phase.
  PP_UNUSED_PARAM(p_cmd);
  PP_UNUSED_PARAM(p_resp);

  *p_err = FS_DEV_SD_CARD_ERR_NONE;
}

/********************************************************************************************************
 *                                      BSP_FS_SD_Card_CmdDataRd()
 *
 * Description : Read data following command.
 *
 * Argument(s) : p_cmd       Pointer to command that was started.
 *
 *               p_dest      Pointer to destination buffer.
 *
 *               p_err       Pointer to variable that will receive the return error code from this function :
 *
 *                               FS_DEV_SD_CARD_ERR_NONE              No error.
 *                               FS_DEV_SD_CARD_ERR_NO_CARD           No card present.
 *                               FS_DEV_SD_CARD_ERR_UNKNOWN           Unknown or other error.
 *                               FS_DEV_SD_CARD_ERR_WAIT_TIMEOUT      Timeout in waiting for data.
 *                               FS_DEV_SD_CARD_ERR_DATA_OVERRUN      Data overrun.
 *                               FS_DEV_SD_CARD_ERR_DATA_TIMEOUT      Timeout in receiving data.
 *                               FS_DEV_SD_CARD_ERR_DATA_CHKSUM       Error in data checksum.
 *                               FS_DEV_SD_CARD_ERR_DATA_START_BIT    Data start bit error.
 *                               FS_DEV_SD_CARD_ERR_DATA              Other data error.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_CmdDataRd(FS_DEV_SD_CARD_CMD *p_cmd,
                                     void               *p_dest,
                                     FS_DEV_SD_CARD_ERR *p_err)
{
  RTOS_ERR err;

  //                                                               Wait for data transfer completion.
  KAL_SemPend(BSP_FS_SD_Card_Data.OS_Sem, KAL_OPT_PEND_BLOCKING, SD_CARD_WAIT_TIMEOUT_MS, &err);
  if (RTOS_ERR_CODE_GET(err) != RTOS_ERR_NONE) {
    return;
  }

  //                                                               TODO: Add command data read instructions to retrieve the data sent by the SD card.
  PP_UNUSED_PARAM(p_cmd);
  PP_UNUSED_PARAM(p_dest);

  *p_err = FS_DEV_SD_CARD_ERR_NONE;
}

/********************************************************************************************************
 *                                      BSP_FS_SD_Card_CmdDataWr()
 *
 * Description : Write data following command.
 *
 * Argument(s) : p_cmd       Pointer to command that was started.
 *
 *               p_src       Pointer to source buffer.
 *
 *               p_err       Pointer to variable that will receive the return error code from this function :
 *
 *                               FS_DEV_SD_CARD_ERR_NONE              No error.
 *                               FS_DEV_SD_CARD_ERR_NO_CARD           No card present.
 *                               FS_DEV_SD_CARD_ERR_UNKNOWN           Unknown or other error.
 *                               FS_DEV_SD_CARD_ERR_WAIT_TIMEOUT      Timeout in waiting for data.
 *                               FS_DEV_SD_CARD_ERR_DATA_UNDERRUN     Data underrun.
 *                               FS_DEV_SD_CARD_ERR_DATA_CHKSUM       Err in data checksum.
 *                               FS_DEV_SD_CARD_ERR_DATA_START_BIT    Data start bit error.
 *                               FS_DEV_SD_CARD_ERR_DATA              Other data error.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_CmdDataWr(FS_DEV_SD_CARD_CMD *p_cmd,
                                     void               *p_src,
                                     FS_DEV_SD_CARD_ERR *p_err)
{
  //                                                               TODO: Prepare data write transfer.
  RTOS_ERR err;
  PP_UNUSED_PARAM(p_cmd);
  PP_UNUSED_PARAM(p_src);

  //                                                               Wait for data transfer completion.
  KAL_SemPend(BSP_FS_SD_Card_Data.OS_Sem,
              KAL_OPT_PEND_BLOCKING,
              SD_CARD_WAIT_TIMEOUT_MS,
              &err);

  //                                                               TODO: Determine if transfer has completed with or without error.

  *p_err = FS_DEV_SD_CARD_ERR_NONE;
}

/********************************************************************************************************
 *                                     BSP_FS_SD_Card_BlkCntMaxGet()
 *
 * Description : Get maximum number of blocks that can be transferred with a multiple read or multiple
 *               write command.
 *
 * Argument(s) : blk_size    Block size, in octets.
 *
 * Return(s)   : Maximum number of blocks.
 *
 * Note(s)     : (1) The controller has no limit on the number of blocks in a multiple block read or
 *                   write, so'DEF_INT_32U_MAX_VAL' should be returned.
 *
 *               (2) This function SHOULD always return the same value.  If hardware constraints change
 *                   at run-time, the device MUST be closed & re-opened for any changes to be effective.
 *******************************************************************************************************/
static CPU_INT32U BSP_FS_SD_Card_BlkCntMaxGet(CPU_INT32U blk_size)
{
  PP_UNUSED_PARAM(blk_size);

  return (DEF_INT_32U_MAX_VAL);
}

/********************************************************************************************************
 *                                    BSP_FS_SD_Card_BusWidthMaxGet()
 *
 * Description : Get maximum bus width, in bits.
 *
 * Argument(s) : None.
 *
 * Return(s)   : Maximum bus width.
 *
 * Note(s)     : (1) The MMC interface is capable of 1- & 4-bit operation.
 *
 *               (2) This function SHOULD always return the same value.  If hardware constraints change
 *                   at run-time, the device MUST be closed & re-opened for any changes to be effective.
 *******************************************************************************************************/
static CPU_INT08U BSP_FS_SD_Card_BusWidthMaxGet(void)
{
  return (4u);
}

/********************************************************************************************************
 *                                     BSP_FS_SD_Card_BusWidthSet()
 *
 * Description : Set bus width.
 *
 * Argument(s) : width       Bus width, in bits.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_BusWidthSet(CPU_INT08U width)
{
  //                                                               TODO: Set the bus width in the SD Card controller to match the SD card configuration.
  PP_UNUSED_PARAM(width);
}

/********************************************************************************************************
 *                                      BSP_FS_SD_Card_ClkFreqSet()
 *
 * Description : Set clock frequency.
 *
 * Argument(s) : freq        Clock frequency, in Hz.
 *
 * Return(s)   : None.
 *
 * Note(s)     : (1) The effective clock frequency MUST be no more than 'freq'.  If the frequency cannot be
 *                   configured equal to 'freq', it should be configured less than 'freq'.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_ClkFreqSet(CPU_INT32U freq)
{
  //                                                               TODO: Set the clock frequency outputted to the SD Card.
  PP_UNUSED_PARAM(freq);
}

/********************************************************************************************************
 *                                    BSP_FS_SD_Card_TimeoutDataSet()
 *
 * Description : Set data timeout.
 *
 * Argument(s) : to_clks     Timeout, in clocks.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_TimeoutDataSet(CPU_INT32U to_clks)
{
  //                                                               TODO: Add timeout data set instructions, if available.
  PP_UNUSED_PARAM(to_clks);
}

/********************************************************************************************************
 *                                    BSP_FS_SD_Card_TimeoutRespSet()
 *
 * Description : Set response timeout.
 *
 * Argument(s) : to_ms       Timeout, in milliseconds.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_TimeoutRespSet(CPU_INT32U to_ms)
{
  //                                                               TODO: Set the timeout for the response phase.
  //                                                               Some SD Card controller provides a hardware timeout. In that case, this function does nothing special.
  PP_UNUSED_PARAM(to_ms);
}

/********************************************************************************************************
 ********************************************************************************************************
 *                                           LOCAL FUNCTIONS
 ********************************************************************************************************
 *******************************************************************************************************/

/********************************************************************************************************
 *                                     BSP_FS_SD_Card_ISR_Handler()
 *
 * Description : Interrupt handler for the SDIO controller.
 *
 * Argument(s) : None.
 *
 * Return(s)   : None.
 *
 * Note(s)     : None.
 *******************************************************************************************************/
static void BSP_FS_SD_Card_ISR_Handler(void)
{
  //                                                               TODO: Add interrupt handler instructions related to SD Card controller
}

/********************************************************************************************************
 ********************************************************************************************************
 *                                   DEPENDENCIES & AVAIL CHECK(S) END
 ********************************************************************************************************
 *******************************************************************************************************/

#endif // RTOS_MODULE_FS_AVAIL && RTOS_MODULE_FS_STORAGE_SD_CARD_AVAIL