#include "mex.hpp"
#include "mexAdapter.hpp"

#include "Vector.pb.h"
#include <string>
#include <vector>

class MexFunction : public matlab::mex::Function
{
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        checkArguments(outputs, inputs);
        
        matlab::data::TypedArray<uint8_t> inArray = inputs[0];
        std::string buffer = std::string(inArray.begin(),inArray.end());
        
        vec16 protobufobj;
        protobufobj.ParseFromString(buffer);
        
        outputs[0] = factory.createArray<double>(std::vector<size_t>({16}),
        {
            protobufobj.s0(),
            protobufobj.s1(),
            protobufobj.s2(),
            protobufobj.s3(),
            protobufobj.s4(),
            protobufobj.s5(),
            protobufobj.s6(),
            protobufobj.s7(),
            protobufobj.s8(),
            protobufobj.s9(),
            protobufobj.sa(),
            protobufobj.sb(),
            protobufobj.sc(),
            protobufobj.sd(),
            protobufobj.se(),
            protobufobj.sf()
        });
    }
    
    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        if (inputs.size() != 1) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("One input required") }));
        }
        
        if (inputs[0].getType() != matlab::data::ArrayType::UINT8) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("Input array must be type unit8") }));
        }
    }
private:
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    matlab::data::ArrayFactory factory;
};