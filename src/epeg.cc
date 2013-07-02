#include <node.h>
#include <v8.h>

#include <string.h>

#include "Epeg.h"

using namespace v8;

#define DEFAULT_QUALITY 85;

Handle<Value> Resize(const Arguments& args) {
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
    int width = args[2]->NumberValue();
    int height = args[3]->NumberValue();

    int quality = DEFAULT_QUALITY;
    if (args[4]->IsNumber())
        quality = args[4]->NumberValue();

    im = epeg_file_open(*input_file);
    if (!im) {
        ThrowException(Exception::TypeError(String::New("Cannot open input file")));
        return scope.Close(Undefined());
    }
    epeg_file_output_set(im, *output_file);

    epeg_quality_set(im, quality);

    epeg_decode_size_set(im, width, height);
    epeg_encode(im);
    epeg_close(im);

    return scope.Close(v8::Boolean::New(true));
}

Handle<Value> Crop(const Arguments& args) {
    HandleScope  scope;
    Epeg_Image * im;

    if (args.Length() < 6) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsString() ||
        !args[1]->IsString() ||
        !args[2]->IsNumber() ||
        !args[3]->IsNumber() ||
        !args[4]->IsNumber() ||
        !args[5]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    String::AsciiValue input_file(args[0]->ToString());
    String::AsciiValue output_file(args[1]->ToString());
    int x = args[2]->NumberValue();
    int y = args[3]->NumberValue();
    int width = args[4]->NumberValue();
    int height = args[5]->NumberValue();

    int quality = DEFAULT_QUALITY;
    if (args[6]->IsNumber())
        quality = args[6]->NumberValue();

    im = epeg_file_open(*input_file);
    if (!im) {
        ThrowException(Exception::TypeError(String::New("Cannot open input file")));
        return scope.Close(Undefined());
    }
    epeg_file_output_set(im, *output_file);

    epeg_quality_set(im, quality);

    epeg_decode_bounds_set(im, x, y, width, height);
    epeg_trim(im);
    epeg_close(im);

    return scope.Close(v8::Boolean::New(true));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("resize"),
                 FunctionTemplate::New(Resize)->GetFunction());
    exports->Set(String::NewSymbol("crop"),
                 FunctionTemplate::New(Crop)->GetFunction());
}

NODE_MODULE(epeg, init)
