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
        
        vec16 protobufobj;

        protobufobj.set_s0(inputs[0][0]);
        protobufobj.set_s1(inputs[0][1]);
        protobufobj.set_s2(inputs[0][2]);
        protobufobj.set_s3(inputs[0][3]);
        protobufobj.set_s4(inputs[0][4]);
        protobufobj.set_s5(inputs[0][5]);
        protobufobj.set_s6(inputs[0][6]);
        protobufobj.set_s7(inputs[0][7]);
        protobufobj.set_s8(inputs[0][8]);
        protobufobj.set_s9(inputs[0][9]);
        protobufobj.set_sa(inputs[0][10]);
        protobufobj.set_sb(inputs[0][11]);
        protobufobj.set_sc(inputs[0][12]);
        protobufobj.set_sd(inputs[0][13]);
        protobufobj.set_se(inputs[0][14]);
        protobufobj.set_sf(inputs[0][15]);

        std::string buffer = std::string();
        protobufobj.SerializeToString(&buffer);
        
        std::vector<uint8_t> temp = std::vector<uint8_t>(buffer.begin(), buffer.end());
        
        outputs[0] = factory.createArray(std::vector<size_t>({temp.size()}), temp.begin(), temp.end());
        
    }
    
    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        if (inputs.size() != 1) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("One input required") }));
        }

        if (inputs[0].getType() != matlab::data::ArrayType::DOUBLE) {
            matlabPtr->feval(u"error", 
                0, std::vector<matlab::data::Array>({ factory.createScalar("Input array must be type double") }));
        }
    }
private:
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    matlab::data::ArrayFactory factory;
};