#include "DWLoadLib.h"

#include <pybind11/pybind11.h>


#include <iostream>


namespace py = pybind11;

int dw(){
    int i, j, k, l;
    struct DWFileInfo fi;
    __int64 sample_cnt;
    double* data;
    char* binData;
    void* raw_data;
    struct DWCANPortData* CANPortData;
    struct DWComplex* complex_data;
    double* time_stamp;
    int ch_list_cnt;
    int multifile_id;
    struct DWChannel* ch_list;
    int event_list_cnt;
    struct DWEvent* event_list;
    int reduced_data_cnt;
    struct DWReducedValue* reduced_data;
    double block_size;
    char str[256];
    char* text_values;
    int array_info_cnt;
    struct DWArrayInfo* array_info_list;
    double ch_scale, ch_offset;
    void* ret_buff;
    int max_len, data_type, file_index, num_readers, xml_len, xml_props_len, data_type_len;
    int* data_types;
    int* data_type_lens;
    enum DWChannelType channel_type;
    char* out_text;
    char* stream_name;
    int success;
    int data_len, data_offset;
    const int MAX_BIN_SAMPLES = 100;
    const int MAX_BIN_LEN = 10000;
    int read_samples;

    #ifdef _WIN32
        #ifdef _WIN64
            printf("WIN x64 Application\n");
            const char* DLL_PATH = TEXT("DWDataReaderLib64.dll");
        #else
            printf("WIN x86 Application\n");
            const char* DLL_PATH = TEXT("DWDataReaderLib.dll");
        #endif
    #else
        const char DLL_PATH[] = "DWDataReaderLib.so";
    #endif

    if (!LoadDWDLL(DLL_PATH))// Load DLL
    {
        std::cout << "Could not load dll object\n";
        return 0;
    }

    DWInit(); //initiate dll
    std::cout << "DW Version = " << DWGetVersion() << "\n\n"; //Get dll version

    if (!DWOpenDataFile("", &fi)){

    }
    
    return 1;

}

float square(float x) {
    return x * x;
}

PYBIND11_MODULE(PyBind11Example, m) {
    m.def("square", &square);
    m.def("dw", &dw);
}

