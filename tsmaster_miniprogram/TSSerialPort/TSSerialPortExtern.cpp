#include "TSMaster.h"
#include "MPLibrary.h"
#include "Configuration.h"
#include "TSMasterBaseInclude.h"
#include <memory>
#include <string>
#include <vector>
#include "libserialport.h"

// Variables definition
TTSApp app;
TTSCOM com;
TTSTest test;

// Templates Instantiation
template <>
void output<TCAN>(TCAN* canMsg) {
    com.transmit_can_async(canMsg);
}

template <>
void output<TLIN>(TLIN* linMsg) {
    com.transmit_lin_async(linMsg);
}

template <>
void output<TFlexRay>(TFlexRay* frMsg) {
    com.transmit_flexray_async(frMsg);
}

template <>
void output<TEthernetHeader>(TEthernetHeader* ethMsg) {
    com.transmit_ethernet_async(ethMsg);
}

// logger functions definition
#define TEMP_STR_LEN 1024
typedef char* va_list;
#ifndef __va_rounded_size
#define __va_rounded_size(TYPE) (((sizeof(TYPE)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#endif
 
#ifndef va_start
#define va_start(AP, LASTARG)   (AP = ((char *)& (LASTARG) + __va_rounded_size(LASTARG)))
#endif
 
#ifndef va_arg
#define va_arg(AP, TYPE)        (AP += __va_rounded_size(TYPE), *((TYPE *)(AP - __va_rounded_size(TYPE))))
#endif
 
#ifndef va_end
#define va_end(AP)              (AP = (va_list)0 )
#endif

// Utility functions definition
void internal_log(const char* AFile, const char* AFunc, const s32 ALine, const TLogLevel ALevel, const char* fmt, ...)
{ 
  va_list ap;    
  va_start(ap, fmt);
  std::vector<char> buf(1024);
  int ret;  
#if __cplusplus == 201103L
  while((ret = vsnprintf_s(&buf[0], buf.size(), fmt, ap)) == -1){
#else
  // in VC++ version is 199711L, log("__cplusplus: %d\n", __cplusplus);
  while ((ret = vsnprintf_s(&buf[0], buf.size(), buf.size(), fmt, ap)) == -1) {
#endif
    buf.resize(buf.size() * 2);    
  }
  va_end(ap);
  if (ret == static_cast<int>(buf.size())){
    buf[buf.size() - 1] = '\0';    
  }         
  app.debug_log(AFile, AFunc, ALine, &buf[0], ALevel);
}

void internal_test_log(const char* AFile, const char* AFunc, const s32 ALine, const TLogLevel ALevel, const char* fmt, ...)
{ 
  va_list ap;    
  va_start(ap, fmt);
  std::vector<char> buf(1024);
  int ret;  
#if __cplusplus == 201103L
  while ((ret = vsnprintf_s(&buf[0], buf.size(), fmt, ap)) == -1) {
#else
  while ((ret = vsnprintf_s(&buf[0], buf.size(), buf.size(), fmt, ap)) == -1) {
#endif
    buf.resize(buf.size() * 2);    
  }
  va_end(ap);
  if (ret == static_cast<int>(buf.size())){
    buf[buf.size() - 1] = '\0';    
  }         
  test.debug_log_info(AFile, AFunc, ALine, &buf[0], ALevel);
}

void test_logCAN(const char* ADesc, PCAN ACAN, const TLogLevel ALevel)
{
    char s[TEMP_STR_LEN];
    // channel, id, dlc, [data]
    if (ACAN->is_tx){
        if (ACAN->is_data){
            sprintf(s, "%s %d %03X Tx d %d [%02X %02X %02X %02X %02X %02X %02X %02X]", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC, ACAN->FData[0], ACAN->FData[1], ACAN->FData[2], ACAN->FData[3], ACAN->FData[4], ACAN->FData[5], ACAN->FData[6], ACAN->FData[7]);
        } else {
            sprintf(s, "%s %d %03X Tx r %d", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC);
        }
    } else {
        if (ACAN->is_data){
            sprintf(s, "%s %d %03X Rx d %d [%02X %02X %02X %02X %02X %02X %02X %02X]", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC, ACAN->FData[0], ACAN->FData[1], ACAN->FData[2], ACAN->FData[3], ACAN->FData[4], ACAN->FData[5], ACAN->FData[6], ACAN->FData[7]);
        } else {
            sprintf(s, "%s %d %03X Rx r %d", ADesc, ACAN->FIdxChn, ACAN->FIdentifier, ACAN->FDLC);
        }
    }
    test.log_info(s, ALevel);
}

DLLEXPORT s32 __stdcall initialize_miniprogram(const PTSMasterConfiguration AConf)
{
    app = AConf->FTSApp;
    com = AConf->FTSCOM;
    test = AConf->FTSTest;
    return 0;
    
}

DLLEXPORT s32 __stdcall finalize_miniprogram(void)
{
    return 0;
    
}

// MP library functions definition

// Retrieve TSMP abilities
typedef s32 (__stdcall* TRegTSMasterFunction)(const void* AObj, const char* AFuncType, const char* AFuncName, const char* AData, const void* AFuncPointer, const char* ADescription);
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	s32 tsp_get_port_by_name(const char* portname, struct sp_port** port_ptr);
	s32 tsp_free_port(struct sp_port* port);
	s32 tsp_list_ports(struct sp_port*** list_ptr);
	s32 tsp_copy_port(const struct sp_port* port, struct sp_port** copy_ptr);
	s32 tsp_free_port_list(struct sp_port** ports);
	s32 tsp_open(struct sp_port* port, int flags);
	s32 tsp_close(struct sp_port* port);
	s32 tsp_get_port_name(const struct sp_port* port, char** const name);
	s32 tsp_get_port_description(const struct sp_port* port, char** const description);
	s32 tsp_get_port_transport(const struct sp_port* port);
	s32 tsp_get_port_usb_bus_address(const struct sp_port* port, int* usb_bus, int* usb_address);
	s32 tsp_get_port_usb_vid_pid(const struct sp_port* port, int* usb_vid, int* usb_pid);
	s32 tsp_get_port_usb_manufacturer(const struct sp_port* port, char** const manufacturer);
	s32 tsp_get_port_usb_product(const struct sp_port* port, char** const product);
	s32 tsp_get_port_usb_serial(const struct sp_port* port, char** const serial);
	s32 tsp_get_port_bluetooth_address(const struct sp_port* port, char** const address);
	s32 tsp_get_port_handle(const struct sp_port* port, void* result_ptr);
	s32 tsp_new_config(struct sp_port_config** config_ptr);
	s32 tsp_free_config(struct sp_port_config* config);
	s32 tsp_get_config(struct sp_port* port, struct sp_port_config* config);
	s32 tsp_set_config(struct sp_port* port, const struct sp_port_config* config);
	s32 tsp_set_baudrate(struct sp_port* port, int baudrate);
	
	s32 tsp_get_config_baudrate(const struct sp_port_config* config, int* baudrate_ptr);
	s32 tsp_set_config_baudrate(struct sp_port_config* config, int baudrate);
	s32 tsp_set_bits(struct sp_port* port, int bits);
	s32 tsp_get_config_bits(const struct sp_port_config* config, int* bits_ptr);
	s32 tsp_set_config_bits(struct sp_port_config* config, int bits);
	s32 tsp_set_parity(struct sp_port* port, int parity);
	s32 tsp_get_config_parity(const struct sp_port_config* config, int* parity_ptr);
	s32 tsp_set_config_parity(struct sp_port_config* config, int parity);
	s32 tsp_set_stopbits(struct sp_port* port, int stopbits);
	s32 tsp_get_config_stopbits(const struct sp_port_config* config, int* stopbits_ptr);
	s32 tsp_set_config_stopbits(struct sp_port_config* config, int stopbits);
	s32 tsp_set_rts(struct sp_port* port, int rts);
	
	s32 tsp_get_config_rts(const struct sp_port_config* config, int* rts_ptr);
	s32 tsp_set_config_rts(struct sp_port_config* config, int rts);
	s32 tsp_set_cts(struct sp_port* port, int cts);
	s32 tsp_get_config_cts(const struct sp_port_config* config, int* cts_ptr);
	s32 tsp_set_config_cts(struct sp_port_config* config, int cts);
	s32 tsp_set_dtr(struct sp_port* port, int dtr);
	s32 tsp_get_config_dtr(const struct sp_port_config* config, int* dtr_ptr);
	s32 tsp_set_config_dtr(struct sp_port_config* config, int dtr);
	s32 tsp_set_dsr(struct sp_port* port, int dsr);
	
	s32 tsp_get_config_dsr(const struct sp_port_config* config, int* dsr_ptr);
	s32 tsp_set_config_dsr(struct sp_port_config* config, int dsr);
	s32 tsp_set_xon_xoff(struct sp_port* port, int xon_xoff);
	s32 tsp_get_config_xon_xoff(const struct sp_port_config* config, int* xon_xoff_ptr);
	s32 tsp_set_config_xon_xoff(struct sp_port_config* config, int xon_xoff);
	s32 tsp_set_config_flowcontrol(struct sp_port_config* config, int flowcontrol);
	s32 tsp_set_flowcontrol(struct sp_port* port, int flowcontrol);
	s32 tsp_blocking_read(struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms);
	
	s32 tsp_blocking_read_next(struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms);
	s32 tsp_nonblocking_read(struct sp_port* port, void* buf, size_t count);
	s32 tsp_blocking_write(struct sp_port* port, const void* buf, size_t count, unsigned int timeout_ms);
	s32 tsp_nonblocking_write(struct sp_port* port, const void* buf, size_t count);
	s32 tsp_input_waiting(struct sp_port* port);
	s32 tsp_output_waiting(struct sp_port* port);
	
	s32 tsp_flush(struct sp_port* port, int buffers);
	s32 tsp_drain(struct sp_port* port);
	s32 tsp_new_event_set(struct sp_event_set** result_ptr);
	s32 tsp_add_port_events(struct sp_event_set* event_set, const struct sp_port* port, int mask);
	s32 tsp_wait(struct sp_event_set* event_set, unsigned int timeout_ms);
	s32 tsp_free_event_set(struct sp_event_set* event_set);
	s32 tsp_get_signals(struct sp_port* port, int* signal_mask);
	
	s32 tsp_start_break(struct sp_port* port);
	s32 tsp_end_break(struct sp_port* port);
	s32 tsp_last_error_code(void);
	s32 tsp_last_error_message(char** const message);
	s32 tsp_free_error_message(char* message);
	s32 tsp_set_debug_handler(void (*handler)(const char* format, ...));
	s32 tsp_default_debug_handler(const char* format, ...);

	s32 tsp_get_major_package_version(void);
	s32 tsp_get_minor_package_version(void);
	s32 tsp_get_micro_package_version(void);
	s32 tsp_get_package_version_string(const char** const ver_str);
	s32 tsp_get_current_lib_version(void);
	s32 tsp_get_revision_lib_version(void);
	s32 tsp_get_age_lib_version(void);
	s32 tsp_get_lib_version_string(const char** const ver_str);

#ifdef __cplusplus
}
#endif /* __cplusplus */
DLLEXPORT s32 __stdcall retrieve_mp_abilities(const void* AObj, const TRegTSMasterFunction AReg) {
  #define TSMASTER_VERSION "2024.9.19.1184"
  if (!AReg(AObj, "check_mp_internal", "version", TSMASTER_VERSION, 0, "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_app", (void *)sizeof(TTSMasterConfiguration), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tcan", (void *)sizeof(TCAN), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tcanfd", (void *)sizeof(TCANFD), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tlin", (void *)sizeof(TLIN), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tflexray", (void *)sizeof(TFlexRay), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_tethernetheader", (void *)sizeof(TEthernetHeader), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarInt", (void *)sizeof(TMPVarInt), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarDouble", (void *)sizeof(TMPVarDouble), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarString", (void *)sizeof(TMPVarString), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarCAN", (void *)sizeof(TMPVarCAN), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarCANFD", (void *)sizeof(TMPVarCANFD), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TMPVarLIN", (void *)sizeof(TMPVarLIN), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TLIBTSMapping", (void *)sizeof(TLIBTSMapping), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "struct_size", "struct_size_TLIBSystemVarDef", (void *)sizeof(TLIBSystemVarDef), "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "auto_start", "0", 0, "")) return -1;
  if (!AReg(AObj, "check_mp_internal", "addr_conf", "app", &app, "")) return -1;
  /* user function block start */
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_by_name", "const char* portname, struct sp_port** port_ptr", &tsp_get_port_by_name, "Obtain a pointer to a new sp_port structure representing the named port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_free_port", "struct sp_port* port", &tsp_free_port, "Free a port structure obtained from sp_get_port_by_name() or sp_copy_port().")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_list_ports", "struct sp_port*** list_ptr", &tsp_list_ports, "List the serial ports available on the system.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_copy_port", "const struct sp_port* port, struct sp_port** copy_ptr", &tsp_copy_port, "Make a new copy of an sp_port structure.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_free_port_list", "struct sp_port** ports", &tsp_free_port_list, "Free a port list obtained from sp_list_ports().")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_open", "struct sp_port* port, int flags", &tsp_open, "Open the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_close", "struct sp_port* port", &tsp_close, "Close the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_name", "const struct sp_port* port, char** const name", &tsp_get_port_name, "Get the name of a port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_description", "const struct sp_port* port, char** const description", &tsp_get_port_description, "Get a description for a port, to present to end user.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_transport", "const struct sp_port* port", &tsp_get_port_transport, "Get the transport type used by a port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_usb_bus_address", "const struct sp_port* port, int* usb_bus, int* usb_address", &tsp_get_port_usb_bus_address, "Get the USB bus number and address on bus of a USB serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_usb_vid_pid", "const struct sp_port* port, int* usb_vid, int* usb_pid", &tsp_get_port_usb_vid_pid, "Get the USB Vendor ID and Product ID of a USB serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_usb_manufacturer", "const struct sp_port* port, char** const manufacturer", &tsp_get_port_usb_manufacturer, "Get the USB manufacturer string of a USB serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_usb_product", "const struct sp_port* port, char** const product", &tsp_get_port_usb_product, "Get the USB product string of a USB serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_usb_serial", "const struct sp_port* port, char** const serial", &tsp_get_port_usb_serial, "Get the USB serial number string of a USB serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_bluetooth_address", "const struct sp_port* port, char** const address", &tsp_get_port_bluetooth_address, "Get the MAC address of a Bluetooth serial adapter port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_port_handle", "const struct sp_port* port, void* result_ptr", &tsp_get_port_handle, "Get the operating system handle for a port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_new_config", "struct sp_port_config** config_ptr", &tsp_new_config, "Allocate a port configuration structure.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_free_config", "struct sp_port_config* config", &tsp_free_config, "Free a port configuration structure.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config", "struct sp_port* port, struct sp_port_config* config", &tsp_get_config, "Get the current configuration of the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config", "struct sp_port* port, const struct sp_port_config* config", &tsp_set_config, "Set the configuration for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_baudrate", "struct sp_port* port, int baudrate", &tsp_set_baudrate, "Set the baud rate for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_baudrate", "const struct sp_port_config* config, int* baudrate_ptr", &tsp_get_config_baudrate, "Get the baud rate from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_baudrate", "struct sp_port_config* config, int baudrate", &tsp_set_config_baudrate, "Set the baud rate in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_bits", "struct sp_port* port, int bits", &tsp_set_bits, "Set the data bits for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_bits", "const struct sp_port_config* config, int* bits_ptr", &tsp_get_config_bits, "Get the data bits from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_bits", "struct sp_port_config* config, int bits", &tsp_set_config_bits, "Set the data bits in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_parity", "struct sp_port* port, int parity", &tsp_set_parity, "Set the parity setting for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_parity", "const struct sp_port_config* config, int* parity_ptr", &tsp_get_config_parity, "Get the parity setting from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_parity", "struct sp_port_config* config, int parity", &tsp_set_config_parity, "Set the parity setting in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_stopbits", "struct sp_port* port, int stopbits", &tsp_set_stopbits, "Set the stop bits for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_stopbits", "const struct sp_port_config* config, int* stopbits_ptr", &tsp_get_config_stopbits, "Get the stop bits from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_stopbits", "struct sp_port_config* config, int stopbits", &tsp_set_config_stopbits, "Set the stop bits in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_rts", "struct sp_port* port, int rts", &tsp_set_rts, "Set the RTS pin behaviour for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_rts", "const struct sp_port_config* config, int* rts_ptr", &tsp_get_config_rts, "Get the RTS pin behaviour from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_rts", "struct sp_port_config* config, int rts", &tsp_set_config_rts, "Set the RTS pin behaviour in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_cts", "struct sp_port* port, int cts", &tsp_set_cts, "Set the CTS pin behaviour for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_cts", "const struct sp_port_config* config, int* cts_ptr", &tsp_get_config_cts, "Get the CTS pin behaviour from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_cts", "struct sp_port_config* config, int cts", &tsp_set_config_cts, "Set the CTS pin behaviour in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_dtr", "struct sp_port* port, int dtr", &tsp_set_dtr, "Set the DTR pin behaviour for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_dtr", "const struct sp_port_config* config, int* dtr_ptr", &tsp_get_config_dtr, "Get the DTR pin behaviour from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_dtr", "struct sp_port_config* config, int dtr", &tsp_set_config_dtr, "Set the DTR pin behaviour in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_dsr", "struct sp_port* port, int dsr", &tsp_set_dsr, "Set the DSR pin behaviour for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_dsr", "const struct sp_port_config* config, int* dsr_ptr", &tsp_get_config_dsr, "Get the DSR pin behaviour from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_dsr", "struct sp_port_config* config, int dsr", &tsp_set_config_dsr, "Set the DSR pin behaviour in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_xon_xoff", "struct sp_port* port, int xon_xoff", &tsp_set_xon_xoff, "Set the XON/XOFF configuration for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_config_xon_xoff", "const struct sp_port_config* config, int* xon_xoff_ptr", &tsp_get_config_xon_xoff, "Get the XON/XOFF configuration from a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_xon_xoff", "struct sp_port_config* config, int xon_xoff", &tsp_set_config_xon_xoff, "Set the XON/XOFF configuration in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_config_flowcontrol", "struct sp_port_config* config, int flowcontrol", &tsp_set_config_flowcontrol, "Set the flow control type in a port configuration.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_flowcontrol", "struct sp_port* port, int flowcontrol", &tsp_set_flowcontrol, "Set the flow control type for the specified serial port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_blocking_read", "struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms", &tsp_blocking_read, "Read bytes from the specified serial port, blocking until complete.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_blocking_read_next", "struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms", &tsp_blocking_read_next, "Read bytes from the specified serial port, returning as soon as any data is available.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_nonblocking_read", "struct sp_port* port, void* buf, size_t count", &tsp_nonblocking_read, "Read bytes from the specified serial port, without blocking.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_blocking_write", "struct sp_port* port, const void* buf, size_t count, unsigned int timeout_ms", &tsp_blocking_write, "Write bytes to the specified serial port, blocking until complete.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_nonblocking_write", "struct sp_port* port, const void* buf, size_t count", &tsp_nonblocking_write, "Write bytes to the specified serial port, without blocking.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_input_waiting", "struct sp_port* port", &tsp_input_waiting, "Gets the number of bytes waiting in the input buffer.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_output_waiting", "struct sp_port* port", &tsp_output_waiting, "Gets the number of bytes waiting in the output buffer.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_flush", "struct sp_port* port, int buffers", &tsp_flush, "Flush serial port buffers. Data in the selected buffer(s) is discarded.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_drain", "struct sp_port* port", &tsp_drain, "Wait for buffered data to be transmitted.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_new_event_set", "struct sp_event_set** result_ptr", &tsp_new_event_set, "Allocate storage for a set of events.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_add_port_events", "struct sp_event_set* event_set, const struct sp_port* port, int mask", &tsp_add_port_events, "Add events to a struct sp_event_set for a given port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_wait", "struct sp_event_set* event_set, unsigned int timeout_ms", &tsp_wait, "Wait for any of a set of events to occur.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_free_event_set", "struct sp_event_set* event_set", &tsp_free_event_set, "Free a structure allocated by sp_new_event_set().")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_signals", "struct sp_port* port, int* signal_mask", &tsp_get_signals, "Gets the status of the control signals for the specified port.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_start_break", "struct sp_port* port", &tsp_start_break, "Put the port transmit line into the break state.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_end_break", "struct sp_port* port", &tsp_end_break, "Take the port transmit line out of the break state.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_last_error_code", "void", &tsp_last_error_code, "Get the error code for a failed operation.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_last_error_message", "char** const message", &tsp_last_error_message, "Get the error message for a failed operation.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_free_error_message", "char* message", &tsp_free_error_message, "Free an error message returned by sp_last_error_message().")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_set_debug_handler", "void (*handler)(const char* format, ...)", &tsp_set_debug_handler, "Set the handler function for library debugging messages.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_default_debug_handler", "const char* format, ...", &tsp_default_debug_handler, "Default handler function for library debugging messages.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_major_package_version", "void", &tsp_get_major_package_version, "Get the major libserialport package version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_minor_package_version", "void", &tsp_get_minor_package_version, "Get the minor libserialport package version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_micro_package_version", "void", &tsp_get_micro_package_version, "Get the micro libserialport package version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_package_version_string", "const char** const ver_str", &tsp_get_package_version_string, "Get the libserialport package version number as a string.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_current_lib_version", "void", &tsp_get_current_lib_version, "Get the \"current\" part of the libserialport library version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_revision_lib_version", "void", &tsp_get_revision_lib_version, "Get the \"revision\" part of the libserialport library version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_age_lib_version", "void", &tsp_get_age_lib_version, "Get the \"age\" part of the libserialport library version number.")) return -1;
  if (!AReg(AObj, "on_custom_callback", "tsp_get_lib_version_string", "const char** const ver_str", &tsp_get_lib_version_string, "Get the libserialport library version number as a string.")) return -1;
  /* user function block end */
  // MP library functions

  return 1;
}
