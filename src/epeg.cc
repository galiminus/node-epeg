#include <node.h>
#include <v8.h>

#include <string.h>

#include "Epeg.h"

using namespace v8;

Handle<Value> Method(const Arguments& args) {
    HandleScope  scope;
    Epeg_Image * im;

    if (args.Length() < 4) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsString() ||
        !args[1]->IsString() ||
        !args[2]->IsNumber() ||
        !args[3]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    String::AsciiValue input_file(args[0]->ToString());
    String::AsciiValue output_file(args[1]->ToString());
    unsigned int width = args[2]->NumberValue();
    unsigned int height = args[3]->NumberValue();

    im = epeg_file_open(*input_file);
    if (!im) {
        ThrowException(Exception::TypeError(String::New("Cannot open input file")));
        return scope.Close(Undefined());
    }
    epeg_decode_size_set(im, width, height);
    epeg_file_output_set(im, *output_file);
    epeg_encode(im);
    epeg_close(im);

    return scope.Close(v8::Boolean::New(true));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("resize"),
                 FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(epeg, init)
