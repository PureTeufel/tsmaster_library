// GEN BLOCK BEGIN Include
#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "TSMasterBaseInclude.h"
#include "Configuration.h"
#include "libserialport.h"

#include <stdarg.h>
// GEN BLOCK END Include

// demo
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

s32 tsp_get_port_by_name(const char *portname, struct sp_port **port_ptr)
{
	return (s32)sp_get_port_by_name(portname, port_ptr);
}

s32 tsp_free_port(struct sp_port* port)
{
	sp_free_port(port);
	return 1;
}

s32 tsp_list_ports(struct sp_port*** list_ptr)
{
	return (s32)sp_list_ports(list_ptr);
}

s32 tsp_copy_port(const struct sp_port* port, struct sp_port** copy_ptr)
{
	return (s32)sp_copy_port(port, copy_ptr);
}

s32 tsp_free_port_list(struct sp_port **ports)
{
	sp_free_port_list(ports);
	return 1;
}

s32 tsp_open(struct sp_port* port, int flags)
{
	return (s32)sp_open(port, (enum sp_mode)flags);
}

s32 tsp_close(struct sp_port* port)
{
	return (s32)sp_close(port);
}

s32 tsp_get_port_name(const struct sp_port* port, char** const name)
{
	*name = sp_get_port_name(port);
	
	return 1;
}

s32 tsp_get_port_description(const struct sp_port* port, char** const description)
{
	*description = sp_get_port_description(port);
	return 1;
}

s32 tsp_get_port_transport(const struct sp_port* port)
{
	return (s32)sp_get_port_transport(port);
}

s32 tsp_get_port_usb_bus_address(const struct sp_port* port, int* usb_bus, int* usb_address)
{
	return (s32)sp_get_port_usb_bus_address(port, usb_bus, usb_address);
}

s32 tsp_get_port_usb_vid_pid(const struct sp_port* port, int* usb_vid, int* usb_pid)
{
	return (s32)sp_get_port_usb_vid_pid(port, usb_vid, usb_pid);
}

s32 tsp_get_port_usb_manufacturer(const struct sp_port* port, char** const manufacturer)
{
	*manufacturer = sp_get_port_usb_manufacturer(port);
	return 1;
}

s32 tsp_get_port_usb_product(const struct sp_port* port, char** const product)
{
	*product = sp_get_port_usb_product(port);
	return 1;
}

s32 tsp_get_port_usb_serial(const struct sp_port* port, char** const serial)
{
	*serial = sp_get_port_usb_serial(port);
	return 1;
}

s32 tsp_get_port_bluetooth_address(const struct sp_port* port, char** const address)
{
	*address = sp_get_port_bluetooth_address(port);
	return 1;
}

s32 tsp_get_port_handle(const struct sp_port* port, void* result_ptr)
{
	return (s32)sp_get_port_handle(port, result_ptr);
}

s32 tsp_new_config(struct sp_port_config** config_ptr)
{
	return (s32)sp_new_config(config_ptr);
}

s32 tsp_free_config(struct sp_port_config* config)
{
	sp_free_config(config);
	return 1;
}

s32 tsp_get_config(struct sp_port* port, struct sp_port_config* config)
{
	return (s32)sp_get_config(port, config);
}

s32 tsp_set_config(struct sp_port* port, const struct sp_port_config* config)
{
	return (s32)sp_set_config(port, config);
}

s32 tsp_set_baudrate(struct sp_port* port, int baudrate)
{
	printf("tsp_set_baudrate par1: %llx", port);
	return (s32)sp_set_baudrate(port, baudrate);
}

s32 tsp_get_config_baudrate(const struct sp_port_config* config, int* baudrate_ptr)
{
	return (s32)sp_get_config_baudrate(config, baudrate_ptr);
}

s32 tsp_set_config_baudrate(struct sp_port_config* config, int baudrate)
{
	return (s32)sp_set_config_baudrate(config, baudrate);
}

s32 tsp_set_bits(struct sp_port* port, int bits)
{
	return (s32)sp_set_bits(port, bits);
}

s32 tsp_get_config_bits(const struct sp_port_config* config, int* bits_ptr)
{
	return (s32)sp_get_config_bits(config, bits_ptr);
}

s32 tsp_set_config_bits(struct sp_port_config* config, int bits)
{
	return (s32)sp_set_config_bits(config, bits);
}

s32 tsp_set_parity(struct sp_port* port, int parity)
{
	return (s32)sp_set_parity(port, (enum sp_parity)parity);
}

s32 tsp_get_config_parity(const struct sp_port_config* config, int* parity_ptr)
{
	return (s32)sp_get_config_parity(config, (enum sp_parity*)parity_ptr);
}

s32 tsp_set_config_parity(struct sp_port_config* config, int parity)
{
	return (s32)sp_set_config_parity(config, (enum sp_parity)parity);
}

s32 tsp_set_stopbits(struct sp_port* port, int stopbits)
{
	return sp_set_stopbits(port, stopbits);
}

s32 tsp_get_config_stopbits(const struct sp_port_config* config, int* stopbits_ptr)
{
	return sp_get_config_stopbits(config, stopbits_ptr);
}

s32 tsp_set_config_stopbits(struct sp_port_config* config, int stopbits)
{
	return sp_set_config_stopbits(config, stopbits);
}

s32 tsp_set_rts(struct sp_port* port, int rts)
{
	return (s32)sp_set_rts(port, (enum sp_rts)rts);
}

s32 tsp_get_config_rts(const struct sp_port_config* config, int* rts_ptr)
{
	return sp_get_config_rts(config, (enum sp_rts*)rts_ptr);
}

s32 tsp_set_config_rts(struct sp_port_config* config, int rts)
{
	return sp_set_config_rts(config, (enum sp_rts)rts);
}

s32 tsp_set_cts(struct sp_port* port, int cts)
{
	return sp_set_cts(port, (enum sp_cts)cts);
}

s32 tsp_get_config_cts(const struct sp_port_config* config, int* cts_ptr) 
{
	return (s32)sp_get_config_cts(config, (enum sp_cts*)cts_ptr);
}

s32 tsp_set_config_cts(struct sp_port_config* config, int cts) 
{
	return (s32)sp_set_config_cts(config, (enum sp_cts)cts);
}

s32 tsp_set_dtr(struct sp_port* port, int dtr) 
{
	return (s32)sp_set_dtr(port, (enum sp_dtr)dtr);
}

s32 tsp_get_config_dtr(const struct sp_port_config* config, int* dtr_ptr) 
{
	return sp_get_config_dtr(config, (enum sp_dtr*)dtr_ptr);
}

s32 tsp_set_config_dtr(struct sp_port_config* config, int dtr) 
{
	return (s32)sp_set_config_dtr(config, (enum sp_dtr)dtr);
}

s32 tsp_set_dsr(struct sp_port* port, int dsr) 
{
	return (s32)sp_set_dsr(port, (enum sp_dsr)dsr);
}

s32 tsp_get_config_dsr(const struct sp_port_config* config, int* dsr_ptr) 
{
	return (s32)sp_get_config_dsr(config, (enum sp_dsr*)dsr_ptr);
}

s32 tsp_set_config_dsr(struct sp_port_config* config, int dsr) 
{
	return (s32)sp_set_config_dsr(config, (enum sp_dsr)dsr);
}

s32 tsp_set_xon_xoff(struct sp_port* port, int xon_xoff) 
{
	return (s32)sp_set_xon_xoff(port, (enum sp_xonxoff)xon_xoff);
}

s32 tsp_get_config_xon_xoff(const struct sp_port_config* config, int* xon_xoff_ptr) 
{
	return (s32)sp_get_config_xon_xoff(config, (enum sp_xonxoff*)xon_xoff_ptr);
}

s32 tsp_set_config_xon_xoff(struct sp_port_config* config, int xon_xoff) 
{
	return (s32)sp_set_config_xon_xoff(config, (enum sp_xonxoff)xon_xoff);
}

s32 tsp_set_config_flowcontrol(struct sp_port_config* config, int flowcontrol) 
{
	return (s32)sp_set_config_flowcontrol(config, (enum sp_flowcontrol)flowcontrol);
}

s32 tsp_set_flowcontrol(struct sp_port* port, int flowcontrol) 
{
	return (s32)sp_set_flowcontrol(port, (enum sp_flowcontrol)flowcontrol);
}

s32 tsp_blocking_read(struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms) 
{
	return (s32)sp_blocking_read(port, buf, count, timeout_ms);
}

s32 tsp_blocking_read_next(struct sp_port* port, void* buf, size_t count, unsigned int timeout_ms) 
{
	return (s32)sp_blocking_read_next(port, buf, count, timeout_ms);
}

s32 tsp_nonblocking_read(struct sp_port* port, void* buf, size_t count) 
{
	return (s32)sp_nonblocking_read(port, buf, count);
}

s32 tsp_blocking_write(struct sp_port* port, const void* buf, size_t count, unsigned int timeout_ms) 
{
	return (s32)sp_blocking_write(port, buf, count, timeout_ms);
}

s32 tsp_nonblocking_write(struct sp_port* port, const void* buf, size_t count) 
{
	return (s32)sp_nonblocking_write(port, buf, count);
}

s32 tsp_input_waiting(struct sp_port* port) 
{
	return (s32)sp_input_waiting(port);
}

s32 tsp_output_waiting(struct sp_port* port) 
{
	return (s32)sp_output_waiting(port);
}

s32 tsp_flush(struct sp_port* port, int buffers)
{
	return (s32)sp_flush(port, (enum sp_buffer)buffers);
}

s32 tsp_drain(struct sp_port* port)
{
	return (s32)sp_drain(port);
}

s32 tsp_new_event_set(struct sp_event_set** result_ptr)
{
	return (s32)sp_new_event_set(result_ptr);
}

s32 tsp_add_port_events(struct sp_event_set* event_set, const struct sp_port* port, int mask)
{
	return (s32)sp_add_port_events(event_set, port, (enum sp_event)mask);
}

s32 tsp_wait(struct sp_event_set* event_set, unsigned int timeout_ms)
{
	return (s32)sp_wait(event_set, timeout_ms);
}

s32 tsp_free_event_set(struct sp_event_set* event_set) 
{
	sp_free_event_set(event_set);
	return 1;
}

s32 tsp_get_signals(struct sp_port* port, int* signal_mask)
{
	return (s32)sp_get_signals(port, (enum sp_signal*)signal_mask);
}

s32 tsp_start_break(struct sp_port* port)
{
	return (s32)sp_start_break(port);
}

s32 tsp_end_break(struct sp_port* port)
{
	return (s32)sp_end_break(port);
}

s32 tsp_last_error_code(void) 
{
	return (s32)sp_last_error_code();
}

s32 tsp_last_error_message(char** const message) 
{
	*message = sp_last_error_message();
	return 1;
}

s32 tsp_free_error_message(char* message) 
{
	sp_free_error_message(message);
	return 1;
}

s32 tsp_set_debug_handler(void (*handler)(const char* format, ...))
{
	sp_set_debug_handler(handler);
	return 1;
}

s32 tsp_default_debug_handler(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	sp_default_debug_handler(format, args);
	va_end(args);
	return 1;
}

s32 tsp_get_major_package_version(void)
{
	return (s32)sp_get_major_package_version();
}

s32 tsp_get_minor_package_version(void)
{
	return (s32)sp_get_minor_package_version();
}

s32 tsp_get_micro_package_version(void)
{
	return (s32)sp_get_micro_package_version();
}

s32 tsp_get_package_version_string(const char** const ver_str)
{
	*ver_str = sp_get_package_version_string();
	return 1;
}

s32 tsp_get_current_lib_version(void)
{
	return (s32)sp_get_current_lib_version();
}

s32 tsp_get_revision_lib_version(void)
{
	return (s32)sp_get_revision_lib_version();
}

s32 tsp_get_age_lib_version(void)
{
	return (s32)sp_get_age_lib_version();
}

s32 tsp_get_lib_version_string(const char** const ver_str)
{
	*ver_str = sp_get_lib_version_string();
	return 1;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

