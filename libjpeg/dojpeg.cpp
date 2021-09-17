#include <stdio.h>
#include <string.h>
extern "C" {
#include "jpeglib.h"
};
struct jpegoutput
{
	unsigned int output_width;
	unsigned int output_height;
	int output_components;
	unsigned char* outbuffer;
	int outsize;
};

extern "C" jpegoutput* decodejpeg(unsigned char *buffer, int size)
{
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_mem_src(&cinfo, buffer, size);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	int row_stride = cinfo.output_width * cinfo.output_components;
	JSAMPLE* out = new JSAMPLE[row_stride * cinfo.output_height];
	JSAMPLE* outputptr = out;
	JSAMPARRAY jpegbuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, jpegbuffer, 1);
		memcpy(outputptr, jpegbuffer[0], row_stride);
		outputptr += row_stride;
	}
	jpegoutput* outp = new jpegoutput;
	outp->output_width = cinfo.output_width;
	outp->output_height = cinfo.output_height;
	outp->output_components = cinfo.output_components;
	outp->outbuffer = out;
	outp->outsize = row_stride * cinfo.output_height;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	return outp;
}

extern "C" void freejpeg(jpegoutput * output)
{
	delete[] output->outbuffer;
	delete output;
}