#include "DWLoadLib.h"

#include<vector>
#include <iostream>
#include <chrono>
#include <thread>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void thread_func(const uint64_t& start, const uint64_t& stop){
    uint64_t x = 0;
    
    for(uint64_t i = start; i < stop; i++){
        x = i * i;
        std::cout << x << std::endl;
    }

    return;
}

int dw(){
    auto start = std::chrono::high_resolution_clock::now();
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
            std::cout << "WIN x64 Application" << std::endl;
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

    if (!DWOpenDataFile("C:/Users/Public/Documents/Dewesoft/Data/Test.dxd", &fi)){
        std::cout <<"Sample Rate: "<< fi.sample_rate << std::endl;
        std::cout <<"Start Store Time: " << fi.start_store_time << std::endl;
        std::cout << "Duration: " << fi.duration << std::endl;

        //Get number of channels
        int channelCount = DWGetChannelListCount();

        std::cout << "Channel Count: " << channelCount << std::endl;

        std::vector<DWChannel> channel_list(channelCount);

        std::cout << "Len: " << channel_list.size() << std::endl;
        DWGetChannelList(channel_list.data());// get all channels
        std::cout << "Len: " << channel_list.size() << std::endl;

        for(auto channel : channel_list) {

            std::cout << channel.name << std::endl;

            sample_cnt = DWGetScaledSamplesCount(channel.index);//get channel sample count

            if (sample_cnt < 0)
                std::cout << "ERROR" << std::endl;

            std::vector<double> data_array(sample_cnt);

            std::vector<double> time_stamp_array(sample_cnt);

            if (DWGetScaledSamples(channel.index, 0, sample_cnt, data_array.data(), time_stamp_array.data()) != DWSTAT_OK){//Get channel data
                std::cout << "ERROR" << std::endl;
            }

            else {
                // for(int i = 0; i < data_array.size(); i++) {
                //     std::cout << "Time: " << time_stamp_array[i] << " Value: " << data_array[i] << std::endl;
                // }
            }
            //			printout
            			// for(j = 0; j < sample_cnt; j++)
            			// 	for (k = 0; k < ch_list[i].array_size; k++)
            			// 		printf("Time=%f\tValue=%f\n", time_stamp[j], data[j * ch_list[i].array_size + k]);
            
        
        }



        DWCloseDataFile();
        
    }
    
    DWDeInit();

    uint64_t inc = 999999999 / 4;
    std::thread t1(thread_func, 0*inc, inc*1);
    std::thread t2(thread_func, 1*inc, inc*2);
    std::thread t3(thread_func, 2*inc, 3*inc);
    std::thread t4(thread_func, 3*inc, 4*inc);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Durration: " << duration.count() << std::endl;
    

    
    return 1;

}

float square(float x) {
    return x * x;
}

PYBIND11_MODULE(PyBind11Example, m) {
    m.def("square", &square);
    m.def("dw", &dw);
}

