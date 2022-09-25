//
// dwhci.h
//
// The information in this file is from the Linux HS OTG driver
//    which is Copyright by Synopsys Inc.
//    See the file lib/usb/README!
//
#ifndef _dwhci_h
#define _dwhci_h

#include <circle/bcm2835.h>

#define DWHCI_MAX_CHANNELS          16

#define DWHCI_DATA_FIFO_SIZE        0x1000

//
// コアレジスタ
//
#define DWHCI_CORE_OTG_CTRL         (ARM_USB_CORE_BASE + 0x000)
    #define DWHCI_CORE_OTG_CTRL_HST_SET_HNP_EN      (1 << 10)
#define DWHCI_CORE_OTG_INT          (ARM_USB_CORE_BASE + 0x004)
#define DWHCI_CORE_AHB_CFG          (ARM_USB_CORE_BASE + 0x008)
    #define DWHCI_CORE_AHB_CFG_GLOBALINT_MASK       (1 << 0)
    #define DWHCI_CORE_AHB_CFG_MAX_AXI_BURST__SHIFT 1           // BCM2835 only
    #define DWHCI_CORE_AHB_CFG_MAX_AXI_BURST__MASK  (3 << 1)    // BCM2835 only
    #define DWHCI_CORE_AHB_CFG_WAIT_AXI_WRITES      (1 << 4)    // BCM2835 only
    #define DWHCI_CORE_AHB_CFG_DMAENABLE            (1 << 5)
    #define DWHCI_CORE_AHB_CFG_AHB_SINGLE           (1 << 23)
#define DWHCI_CORE_USB_CFG          (ARM_USB_CORE_BASE + 0x00C)
    #define DWHCI_CORE_USB_CFG_PHYIF                (1 << 3)
    #define DWHCI_CORE_USB_CFG_ULPI_UTMI_SEL        (1 << 4)
    #define DWHCI_CORE_USB_CFG_PHY_SEL_FS           (1 << 6)
    #define DWHCI_CORE_USB_CFG_SRP_CAPABLE          (1 << 8)
    #define DWHCI_CORE_USB_CFG_HNP_CAPABLE          (1 << 9)
    #define DWHCI_CORE_USB_CFG_ULPI_FSLS            (1 << 17)
    #define DWHCI_CORE_USB_CFG_ULPI_CLK_SUS_M       (1 << 19)
    #define DWHCI_CORE_USB_CFG_ULPI_EXT_VBUS_DRV    (1 << 20)
    #define DWHCI_CORE_USB_CFG_TERM_SEL_DL_PULSE    (1 << 22)
#define DWHCI_CORE_RESET            (ARM_USB_CORE_BASE + 0x010)
    #define DWHCI_CORE_RESET_SOFT_RESET             (1 << 0)
    #define DWHCI_CORE_RESET_RX_FIFO_FLUSH          (1 << 4)
    #define DWHCI_CORE_RESET_TX_FIFO_FLUSH          (1 << 5)
    #define DWHCI_CORE_RESET_TX_FIFO_NUM__SHIFT     6
    #define DWHCI_CORE_RESET_TX_FIFO_NUM__MASK      (0x1F << 6)
    #define DWHCI_CORE_RESET_AHB_IDLE               (1 << 31)
#define DWHCI_CORE_INT_STAT         (ARM_USB_CORE_BASE + 0x014)
    #define DWHCI_CORE_INT_STAT_SOF_INTR            (1 << 3)
    #define DWHCI_CORE_INT_STAT_PORT_INTR           (1 << 24)
    #define DWHCI_CORE_INT_STAT_HC_INTR             (1 << 25)
#define DWHCI_CORE_INT_MASK         (ARM_USB_CORE_BASE + 0x018)
    #define DWHCI_CORE_INT_MASK_MODE_MISMATCH       (1 << 1)
    #define DWHCI_CORE_INT_MASK_SOF_INTR            (1 << 3)
    #define DWHCI_CORE_INT_MASK_RX_STS_Q_LVL        (1 << 4)
    #define DWHCI_CORE_INT_MASK_USB_SUSPEND         (1 << 11)
    #define DWHCI_CORE_INT_MASK_PORT_INTR           (1 << 24)
    #define DWHCI_CORE_INT_MASK_HC_INTR             (1 << 25)
    #define DWHCI_CORE_INT_MASK_CON_ID_STS_CHNG     (1 << 28)
    #define DWHCI_CORE_INT_MASK_DISCONNECT          (1 << 29)
    #define DWHCI_CORE_INT_MASK_SESS_REQ_INTR       (1 << 30)
    #define DWHCI_CORE_INT_MASK_WKUP_INTR           (1 << 31)
#define DWHCI_CORE_RX_STAT_RD           (ARM_USB_CORE_BASE + 0x01C)    // RO, slave mode only
#define DWHCI_CORE_RX_STAT_POP          (ARM_USB_CORE_BASE + 0x020)    // RO, slave mode only
    // for read and pop register in host mode
    #define DWHCI_CORE_RX_STAT_CHAN_NUMBER__MASK    0xF
    #define DWHCI_CORE_RX_STAT_BYTE_COUNT__SHIFT    4
    #define DWHCI_CORE_RX_STAT_BYTE_COUNT__MASK     (0x7FF << 4)
    #define DWHCI_CORE_RX_STAT_PACKET_STATUS__SHIFT 17
    #define DWHCI_CORE_RX_STAT_PACKET_STATUS__MASK  (0xF << 17)
        #define DWHCI_CORE_RX_STAT_PACKET_STATUS_IN                 2
        #define DWHCI_CORE_RX_STAT_PACKET_STATUS_IN_XFER_COMP       3
        #define DWHCI_CORE_RX_STAT_PACKET_STATUS_DATA_TOGGLE_ERR    5
        #define DWHCI_CORE_RX_STAT_PACKET_STATUS_CHAN_HALTED        7
#define DWHCI_CORE_RX_FIFO_SIZ          (ARM_USB_CORE_BASE + 0x024)
#define DWHCI_CORE_NPER_TX_FIFO_SIZ     (ARM_USB_CORE_BASE + 0x028)
#define DWHCI_CORE_NPER_TX_STAT         (ARM_USB_CORE_BASE + 0x02C)    // RO
    #define DWHCI_CORE_NPER_TX_STAT_QUEUE_SPACE_AVL(reg)            (((reg) >> 16) & 0xFF)
#define DWHCI_CORE_I2C_CTRL             (ARM_USB_CORE_BASE + 0x030)
#define DWHCI_CORE_PHY_VENDOR_CTRL      (ARM_USB_CORE_BASE + 0x034)
#define DWHCI_CORE_GPIO                 (ARM_USB_CORE_BASE + 0x038)
#define DWHCI_CORE_USER_ID              (ARM_USB_CORE_BASE + 0x03C)
#define DWHCI_CORE_VENDOR_ID            (ARM_USB_CORE_BASE + 0x040)
#define DWHCI_CORE_HW_CFG1              (ARM_USB_CORE_BASE + 0x044)    // RO
#define DWHCI_CORE_HW_CFG2              (ARM_USB_CORE_BASE + 0x048)    // RO
    #define DWHCI_CORE_HW_CFG2_OP_MODE(reg)         (((reg) >> 0) & 7)
    #define DWHCI_CORE_HW_CFG2_ARCHITECTURE(reg)    (((reg) >> 3) & 3)
    #define DWHCI_CORE_HW_CFG2_HS_PHY_TYPE(reg)     (((reg) >> 6) & 3)
        #define DWHCI_CORE_HW_CFG2_HS_PHY_TYPE_NOT_SUPPORTED    0
        #define DWHCI_CORE_HW_CFG2_HS_PHY_TYPE_UTMI             1
        #define DWHCI_CORE_HW_CFG2_HS_PHY_TYPE_ULPI             2
        #define DWHCI_CORE_HW_CFG2_HS_PHY_TYPE_UTMI_ULPI        3
    #define DWHCI_CORE_HW_CFG2_FS_PHY_TYPE(reg)     (((reg) >> 8) & 3)
        #define DWHCI_CORE_HW_CFG2_FS_PHY_TYPE_DEDICATED        1
    #define DWHCI_CORE_HW_CFG2_NUM_HOST_CHANNELS(reg)   ((((reg) >> 14) & 0xF) + 1)
#define DWHCI_CORE_HW_CFG3              (ARM_USB_CORE_BASE + 0x04C)    // RO
    #define DWHCI_CORE_HW_CFG3_DFIFO_DEPTH(reg)     (((reg) >> 16) & 0xFFFF)
#define DWHCI_CORE_HW_CFG4              (ARM_USB_CORE_BASE + 0x050)    // RO
    #define DWHCI_CORE_HW_CFG4_DED_FIFO_EN          (1 << 25)
    #define DWHCI_CORE_HW_CFG4_NUM_IN_EPS(reg)      (((reg) >> 26) & 0xF)
#define DWHCI_CORE_LPM_CFG              (ARM_USB_CORE_BASE + 0x054)
#define DWHCI_CORE_POWER_DOWN           (ARM_USB_CORE_BASE + 0x058)
#define DWHCI_CORE_DFIFO_CFG            (ARM_USB_CORE_BASE + 0x05C)
    #define DWHCI_CORE_DFIFO_CFG_EPINFO_BASE__SHIFT 16
    #define DWHCI_CORE_DFIFO_CFG_EPINFO_BASE__MASK  (0xFFFF << 16)
#define DWHCI_CORE_ADP_CTRL             (ARM_USB_CORE_BASE + 0x060)
// gap
#define DWHCI_VENDOR_MDIO_CTRL          (ARM_USB_CORE_BASE + 0x080)        // BCM2835 only
#define DWHCI_VENDOR_MDIO_DATA          (ARM_USB_CORE_BASE + 0x084)        // BCM2835 only
#define DWHCI_VENDOR_VBUS_DRV           (ARM_USB_CORE_BASE + 0x088)        // BCM2835 only
// gap
#define DWHCI_CORE_HOST_PER_TX_FIFO_SIZ (ARM_USB_CORE_BASE + 0x100)
// fifo := 0..14 :
#define DWHCI_CORE_DEV_PER_TX_FIFO(fifo) (ARM_USB_CORE_BASE + 0x104 + (fifo)*4)   // dedicated FIFOs on
#define DWHCI_CORE_DEV_TX_FIFO(fifo)     (ARM_USB_CORE_BASE + 0x104 + (fifo)*4)   // dedicated FIFOs off

//
// ホストレジスタ
//
#define DWHCI_HOST_CFG                  (ARM_USB_HOST_BASE + 0x000)
    #define DWHCI_HOST_CFG_FSLS_PCLK_SEL__SHIFT     0
    #define DWHCI_HOST_CFG_FSLS_PCLK_SEL__MASK      (3 << 0)
        #define DWHCI_HOST_CFG_FSLS_PCLK_SEL_30_60_MHZ  0
        #define DWHCI_HOST_CFG_FSLS_PCLK_SEL_48_MHZ     1
        #define DWHCI_HOST_CFG_FSLS_PCLK_SEL_6_MHZ      2
#define DWHCI_HOST_FRM_INTERVAL         (ARM_USB_HOST_BASE + 0x004)
#define DWHCI_HOST_FRM_NUM              (ARM_USB_HOST_BASE + 0x008)
    #define DWHCI_HOST_FRM_NUM_NUMBER(reg)          ((reg) & 0xFFFF)
        #define DWHCI_MAX_FRAME_NUMBER                  0x3FFF
    #define DWHCI_HOST_FRM_NUM_REMAINING(reg)       (((reg) >> 16) & 0xFFFF)
// gap
#define DWHCI_HOST_PER_TX_FIFO_STAT     (ARM_USB_HOST_BASE + 0x010)
#define DWHCI_HOST_ALLCHAN_INT          (ARM_USB_HOST_BASE + 0x014)
#define DWHCI_HOST_ALLCHAN_INT_MASK     (ARM_USB_HOST_BASE + 0x018)
#define DWHCI_HOST_FRMLST_BASE          (ARM_USB_HOST_BASE + 0x01C)
// gap
#define DWHCI_HOST_PORT                 (ARM_USB_HOST_BASE + 0x040)
    #define DWHCI_HOST_PORT_CONNECT                 (1 << 0)
    #define DWHCI_HOST_PORT_CONNECT_CHANGED         (1 << 1)
    #define DWHCI_HOST_PORT_ENABLE                  (1 << 2)
    #define DWHCI_HOST_PORT_ENABLE_CHANGED          (1 << 3)
    #define DWHCI_HOST_PORT_OVERCURRENT             (1 << 4)
    #define DWHCI_HOST_PORT_OVERCURRENT_CHANGED     (1 << 5)
    #define DWHCI_HOST_PORT_RESET                   (1 << 8)
    #define DWHCI_HOST_PORT_POWER                   (1 << 12)
    #define DWHCI_HOST_PORT_SPEED(reg)              (((reg) >> 17) & 3)
        #define DWHCI_HOST_PORT_SPEED_HIGH              0
        #define DWHCI_HOST_PORT_SPEED_FULL              1
        #define DWHCI_HOST_PORT_SPEED_LOW               2
    #define DWHCI_HOST_PORT_DEFAULT_MASK            (  DWHCI_HOST_PORT_CONNECT_CHANGED \
                                 | DWHCI_HOST_PORT_ENABLE       \
                                 | DWHCI_HOST_PORT_ENABLE_CHANGED  \
                                 | DWHCI_HOST_PORT_OVERCURRENT_CHANGED)
// gap
// chan := 0..15 :
#define DWHCI_HOST_CHAN_CHARACTER(chan) (ARM_USB_HOST_BASE + 0x100 + (chan)*0x20)
    #define DWHCI_HOST_CHAN_CHARACTER_MAX_PKT_SIZ__MASK 0x7FF
    #define DWHCI_HOST_CHAN_CHARACTER_EP_NUMBER__SHIFT  11
    #define DWHCI_HOST_CHAN_CHARACTER_EP_NUMBER__MASK   (0xF << 11)
    #define DWHCI_HOST_CHAN_CHARACTER_EP_DIRECTION_IN   (1 << 15)
    #define DWHCI_HOST_CHAN_CHARACTER_LOW_SPEED_DEVICE  (1 << 17)
    #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE__SHIFT    18
    #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE__MASK     (3 << 18)
        #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE_CONTROL   0
        #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE_ISO       1
        #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE_BULK      2
        #define DWHCI_HOST_CHAN_CHARACTER_EP_TYPE_INTERRUPT 3
    #define DWHCI_HOST_CHAN_CHARACTER_MULTI_CNT__SHIFT  20
    #define DWHCI_HOST_CHAN_CHARACTER_MULTI_CNT__MASK   (3 << 20)
    #define DWHCI_HOST_CHAN_CHARACTER_DEVICE_ADDRESS__SHIFT 22
    #define DWHCI_HOST_CHAN_CHARACTER_DEVICE_ADDRESS__MASK  (0x7F << 22)
    #define DWHCI_HOST_CHAN_CHARACTER_PER_ODD_FRAME     (1 << 29)
    #define DWHCI_HOST_CHAN_CHARACTER_DISABLE           (1 << 30)
    #define DWHCI_HOST_CHAN_CHARACTER_ENABLE            (1 << 31)
#define DWHCI_HOST_CHAN_SPLIT_CTRL(chan)    (ARM_USB_HOST_BASE + 0x104 + (chan)*0x20)
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_PORT_ADDRESS__MASK   0x7F
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_HUB_ADDRESS__SHIFT   7
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_HUB_ADDRESS__MASK    (0x7F << 7)
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_XACT_POS__SHIFT      14
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_XACT_POS__MASK       (3 << 14)
        #define DWHCI_HOST_CHAN_SPLIT_CTRL_ALL                  3
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_COMPLETE_SPLIT       (1 << 16)
    #define DWHCI_HOST_CHAN_SPLIT_CTRL_SPLIT_ENABLE         (1 << 31)
#define DWHCI_HOST_CHAN_INT(chan)       (ARM_USB_HOST_BASE + 0x108 + (chan)*0x20)
    #define DWHCI_HOST_CHAN_INT_XFER_COMPLETE       (1 << 0)
    #define DWHCI_HOST_CHAN_INT_HALTED              (1 << 1)
    #define DWHCI_HOST_CHAN_INT_AHB_ERROR           (1 << 2)
    #define DWHCI_HOST_CHAN_INT_STALL               (1 << 3)
    #define DWHCI_HOST_CHAN_INT_NAK                 (1 << 4)
    #define DWHCI_HOST_CHAN_INT_ACK                 (1 << 5)
    #define DWHCI_HOST_CHAN_INT_NYET                (1 << 6)
    #define DWHCI_HOST_CHAN_INT_XACT_ERROR          (1 << 7)
    #define DWHCI_HOST_CHAN_INT_BABBLE_ERROR        (1 << 8)
    #define DWHCI_HOST_CHAN_INT_FRAME_OVERRUN       (1 << 9)
    #define DWHCI_HOST_CHAN_INT_DATA_TOGGLE_ERROR   (1 << 10)
    #define DWHCI_HOST_CHAN_INT_ERROR_MASK          (  DWHCI_HOST_CHAN_INT_AHB_ERROR     \
                                 | DWHCI_HOST_CHAN_INT_STALL         \
                                 | DWHCI_HOST_CHAN_INT_XACT_ERROR    \
                                 | DWHCI_HOST_CHAN_INT_BABBLE_ERROR  \
                                 | DWHCI_HOST_CHAN_INT_FRAME_OVERRUN \
                                 | DWHCI_HOST_CHAN_INT_DATA_TOGGLE_ERROR)
#define DWHCI_HOST_CHAN_INT_MASK(chan)  (ARM_USB_HOST_BASE + 0x10C + (chan)*0x20)
#define DWHCI_HOST_CHAN_XFER_SIZ(chan)  (ARM_USB_HOST_BASE + 0x110 + (chan)*0x20)
    #define DWHCI_HOST_CHAN_XFER_SIZ_BYTES__MASK    0x7FFFF
    #define DWHCI_HOST_CHAN_XFER_SIZ_PACKETS__SHIFT 19
    #define DWHCI_HOST_CHAN_XFER_SIZ_PACKETS__MASK  (0x3FF << 19)
    #define DWHCI_HOST_CHAN_XFER_SIZ_PACKETS(reg)   (((reg) >> 19) & 0x3FF)
    #define DWHCI_HOST_CHAN_XFER_SIZ_PID__SHIFT     29
    #define DWHCI_HOST_CHAN_XFER_SIZ_PID__MASK      (3 << 29)
    #define DWHCI_HOST_CHAN_XFER_SIZ_PID(reg)       (((reg) >> 29) & 3)
        #define DWHCI_HOST_CHAN_XFER_SIZ_PID_DATA0      0
        #define DWHCI_HOST_CHAN_XFER_SIZ_PID_DATA1      2
        #define DWHCI_HOST_CHAN_XFER_SIZ_PID_DATA2      1
        #define DWHCI_HOST_CHAN_XFER_SIZ_PID_MDATA      3    // non-control transfer
        #define DWHCI_HOST_CHAN_XFER_SIZ_PID_SETUP      3
#define DWHCI_HOST_CHAN_DMA_ADDR(chan)  (ARM_USB_HOST_BASE + 0x114 + (chan)*0x20)
// gap
#define DWHCI_HOST_CHAN_DMA_BUF(chan)   (ARM_USB_HOST_BASE + 0x11C + (chan)*0x20)    // DDMA only

//
// データFIFO（非DMAモードのみ）
//
#define DWHCI_DATA_FIFO(chan)           (ARM_USB_HOST_BASE + 0x1000 + (chan)*DWHCI_DATA_FIFO_SIZE)

#endif
