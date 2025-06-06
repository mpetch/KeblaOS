
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


// Common PCI Vendor IDs
typedef enum {
    VENDOR_INTEL       = 0x8086,
    VENDOR_REALTEK     = 0x10EC,
    VENDOR_BROADCOM    = 0x14E4,
    VENDOR_AMD         = 0x1022,
    VENDOR_NVIDIA      = 0x10DE,
    VENDOR_VIA         = 0x1106,
    VENDOR_ATT         = 0x1259,
    VENDOR_QUALCOMM    = 0x17CB,
    VENDOR_AQUANTIA    = 0x1D6A,
    VENDOR_MELLANOX    = 0x15B3,
    VENDOR_VMWARE      = 0x15AD,
    VENDOR_VIRTIO      = 0x1AF4,
    VENDOR_QEMU        = 0x1234  // For some virtual NICs
} pci_vendor_id_t;

typedef enum {
    PCI_CLASS_UNCLASSIFIED = 0x0,
    PCI_CLASS_MASS_STORAGE_CONTROLLER = 0x1,
    PCI_CLASS_NETWORK_CONTROLLER = 0x2,
    PCI_CLASS_DISPLAY_CONTROLLER = 0x3,
    PCI_CLASS_MULTIMEDIA_CONTROLLER = 0x4,
    PCI_CLASS_MEMORY_CONTROLLER = 0x5,
    PCI_CLASS_BRIDGE = 0x6,
    PCI_CLASS_SIMPLE_COMMUNICATION_CONTROLLER = 0x7,
    PCI_CLASS_BASE_SYSTEM_PERIPHERAL = 0x8,
    PCI_CLASS_INPUT_DEVICE_CONTROLLER = 0x9,
    PCI_CLASS_DOCKING_STATION = 0xA,
    PCI_CLASS_PROCESSOR = 0xB,
    PCI_CLASS_SERIAL_BUS_CONTROLLER = 0xC,
    PCI_CLASS_WIRELESS_CONTROLLER = 0xD,
    PCI_CLASS_INTELLIGENT_CONTROLLER = 0xE,
    PCI_CLASS_SATELLITE_COMMUNICATION_CONTROLLER = 0xF,
    PCI_CLASS_ENCRYPTION_CONTROLLER = 0x10,
    PCI_CLASS_SIGNAL_PROCESSING_CONTROLLER = 0x11,
    PCI_CLASS_PROCESSING_ACCELERATOR = 0x12,
    PCI_CLASS_NON_ESSENTIAL_INSTRUMENTATION = 0x13,
    PCI_CLASS_RESERVED_1 = 0x14,  // 0x14 - 0x3F (Reserved)
    PCI_CLASS_COPROCESSOR = 0x40,
    PCI_CLASS_RESERVED_2 = 0x41,  // 0x41 - 0xFE (Reserved)
    PCI_CLASS_UNASSIGNED = 0xFF
}PCIClass;

typedef enum {
    PCI_SUBCLASS_NON_VGA = 0x0,
    PCI_SUBCLASS_VGA_UNCLASSIFIED = 0x1
}PCIUnclassifiedSubclass;

typedef enum {
    PCI_SUBCLASS_IDE = 0x1,
    PCI_SUBCLASS_FLOPY_DISK = 0x2,
    PCI_SUBCLASS_IPI_BUS = 0x3,
    PCI_SUBCLASS_RAID = 0x4,
    PCI_SUBCLASS_ATA = 0x5,
    PCI_SUBCLASS_SERIAL_ATA = 0x6,
    PCI_SUBCLASS_SCSI = 0x7,
    PCI_SUBCLASS_NON_VOLATILE_MEM = 0x8
    // PCI_SUBCLASS_OTHER = 0x80
}PCIStorageSubclass;

typedef enum {
    PCI_SUBCLASS_ETHERNET = 0x0,
    PCI_SUBCLASS_TOKEN_RING = 0x1,
    PCI_SUBCLASS_FDDI = 0x2,
    PCI_SUBCLASS_ATM = 0x3,
    PCI_SUBCLASS_ISDN = 0x4,
    PCI_SUBCLASS_WORLD_FIP = 0x5,
    PCI_SUBCLASS_PIC_MG = 0x6,
    PCI_SUBCLASS_INFINBAND = 0x7,
    PCI_SUBCLASS_FABRIC = 0x8
    // PCI_SUBCLASS_OTHER = 0x80
}PCINetworkSubclass;

typedef enum {
    PCI_SUBCLASS_VGA = 0x0,
    PCI_SUBCLASS_XGA = 0x1,
    PCI_SUBCLASS_3D = 0x2
    // PCI_SUBCLASS_OTHER = 0x80
}PCIDisplaySubclass;

typedef enum {
    PCI_SUBCLASS_MULTIMEDIA_VIDEO = 0x0,
    PCI_SUBCLASS_MULTIMEDIA_AUDIO = 0x1,
    PCI_SUBCLASS_TELEPHONY = 0x2,
    PCI_SUBCLASS_AUDIO = 0x3
    // PCI_SUBCLASS_OTHER = 0x80
}PCIMultimediaSubclass;

typedef enum {
    PCI_SUBCLASS_RAM = 0x0,
    PCI_SUBCLASS_FLASH = 0x1
    // PCI_SUBCLASS_OTHER = 0x80
}PCIMemorySubclass;

typedef enum {
    PCI_SUBCLASS_HOST = 0x0,
    PCI_SUBCLASS_ISA = 0x1,
    PCI_SUBCLASS_EISA = 0x2,
    PCI_SUBCLASS_MCA = 0x3,
    PCI_SUBCLASS_PCI_TO_PCI_1 = 0x4,
    PCI_SUBCLASS_PCMCIA = 0x5,
    PCI_SUBCLASS_NUBUS = 0x6,
    PCI_SUBCLASS_CARD_BUS = 0x7,
    PCI_SUBCLASS_RACE_WAY = 0x8,
    PCI_SUBCLASS_PCI_TO_PCI_2 = 0x9,
    PCI_SUBCLASS_INFINI_BAND_TO_PCI = 0xA
    // PCI_SUBCLASS_OTHER = 0x80
}PCIBridgeSubclass;

typedef enum {
    PCI_SUBCLASS_KEYBOARD = 0x0,
    PCI_SUBCLASS_DIGITIZER_PEN = 0x1,
    PCI_SUBCLASS_MOUSE = 0x2,
    PCI_SUBCLASS_SCANNER = 0x3,
    PCI_SUBCLASS_GAMEPORT = 0x4
    // PCI_SUBCLASS_OTHER = 0x80
}PCIInputDeviceSubclass;

typedef enum {
    PCI_SUBCLASS_FIREWIRE = 0x0,
    PCI_SUBCLASS_ACCESS = 0x1,
    PCI_SUBCLASS_SSA = 0x2,
    PCI_SUBCLASS_USB = 0x3,
    PCI_SUBCLASS_FIBRE = 0x4,
    PCI_SUBCLASS_SMBUS = 0x5,
    PCI_SUBCLASS_INFINI_BAND = 0x6,
    PCI_SUBCLASS_IPMI = 0x7,
    PCI_SUBCLASS_SERCOS = 0x8,
    PCI_SUBCLASS_CANBUS = 0x9
    // PCI_SUBCLASS_OTHER = 0x80
}PCISerialBusSubclass;

typedef enum {
    PCI_SUBCLASS_IRDA = 0x0,
    PCI_SUBCLASS_IR = 0x1,
    PCI_SUBCLASS_RF = 0x2,
    PCI_SUBCLASS_BLUETOOTH = 0x3,
    PCI_SUBCLASS_BROADBAND = 0x4,
    PCI_SUBCLASS_ETHERNET_802_1_a = 0x5,
    PCI_SUBCLASS_ETHERNET_802_1_b = 0x6
    // PCI_SUBCLASS_OTHER = 0x80
}PCIWirelessSubclass;

typedef enum {
    STANDARD_HEADER_SINGLE_FUNCTION = 0x0,
    PCI_TO_PCI_BRIDGE = 0x1,
    CARD_BUS_BRIDGE = 0x2,
    STANDARD_HEADER_MULTI_FUNCTION = 0x80
}HeaderType;


struct pci_device {
    uint8_t bus;                   // Bus number
    uint8_t device;                // Device number
    uint8_t function;              // Function number

    uint16_t vendor_id;            // Vendor ID
    uint16_t device_id;            // Device ID

    uint8_t class_code;            // Class code
    uint8_t subclass_code;         // Subclass code
    uint8_t prog_if;               // Programming interface

    uint8_t revision_id;           // Revision ID

    uint8_t bist;                  // Built-in self-test
    uint8_t cache_line_size;       // Cache line size
    uint8_t latency_timer;         // Latency timer
    uint8_t header_type;           // Header type

    uint32_t base_address_registers[6]; // Base address registers (BARs)
};
typedef struct pci_device pci_device_t;


extern pci_device_t mass_storage_controllers[16];  // Array to store detected mass storage devices
extern size_t mass_storage_count;                  // Counter for mass storage devices

extern pci_device_t network_controllers[16];       // Array to store detected network controllers
extern size_t network_controller_count;            // Counter for network controllers

extern pci_device_t wireless_controllers[16];      // Array to store detected wireless controllers
extern size_t wireless_controller_count;           // Counter for wireless controllers

void pci_scan();



void print_device_info(pci_device_t *device);

