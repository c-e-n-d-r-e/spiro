#pragma once

#include "constants.hpp"
#include "node.h"

namespace cell
{
    namespace interface 
    {
        /**********************************************************************************************************************
        * 
        *  Descriptor
        * 
        **********************************************************************************************************************/
        namespace vca
        {
            const int ctrls  { 1 };
            const int ins    { 3 };
            const int outs   { 2 };

            enum class ctrl { amp };
            enum class in   { a, b, amp };
            enum class out  { a, b };

        }
    }


    class vca_t: public module
    {
        public:

            void process() override
            {
                float v = ctrl[static_cast<int>(interface::vca::ctrl::amp)]->load() + in[static_cast<int>(interface::vca::ctrl::amp)]->load();
                if      (v < 0.0f) v = 0.0f;
                else if (v > 1.0f) v = 1.0f;
                float o = (in[static_cast<int>(interface::vca::in::a)]->load() + in[static_cast<int>(interface::vca::in::b)]->load()) * v; 
                out[static_cast<int>(interface::vca::out::a)].store(o);
                out[static_cast<int>(interface::vca::out::b)].store(o);

            };

            vca_t() 
            {  
                init(interface::vca::ctrls, interface::vca::ins, interface::vca::outs);
                for(int i = 0; i < interface::vca::ins; ++i) in[i] = &zero;
                for(int i = 0; i < interface::vca::ctrls; ++i) ctrl[i] = &zero;

            };
           ~vca_t() {};
    };

}
