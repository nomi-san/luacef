#include "../luacef.h"
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_base_capi.h"

#define DEBUG_REFERENCE_COUNTING 0
// Print only the first execution of the callback,
// ignore the subsequent.
#define DEBUG_CALLBACK(x) { \
    static int first_call = 1; \
    if (first_call == 1) { \
        first_call = 0; \
        printf(x); \
    } \
}

void CEF_CALLBACK add_ref(cef_base_t* self) {
	DEBUG_CALLBACK("cef_base_ref_counted_t.add_ref\n");
	if (DEBUG_REFERENCE_COUNTING)
		printf("+");
}

int CEF_CALLBACK release(cef_base_t* self) {
	DEBUG_CALLBACK("cef_base_ref_counted_t.release\n");
	if (DEBUG_REFERENCE_COUNTING)
		printf("-");
	return 1;
}

int CEF_CALLBACK has_one_ref(cef_base_t* self) {
	DEBUG_CALLBACK("cef_base_ref_counted_t.has_one_ref\n");
	if (DEBUG_REFERENCE_COUNTING)
		printf("=");
	return 1;
}

void initialize_cef_base_ref_counted(cef_base_t* base) {
	printf("initialize_cef_base_ref_counted\n");
	// Check if "size" member was set.
	size_t size = base->size;
	// Let's print the size in case sizeof was used
	// on a pointer instead of a structure. In such
	// case the number will be very high.
	printf("cef_base_ref_counted_t.size = %lu\n", (unsigned long)size);
	if (size <= 0) {
		printf("FATAL: initialize_cef_base failed, size member not set\n");
		//_exit(1);
	}
	base->add_ref = add_ref;
	base->release = release;
	base->has_one_ref = has_one_ref;
}


