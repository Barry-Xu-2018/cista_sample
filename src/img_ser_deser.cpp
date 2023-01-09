#include "cista.h"
#include <iostream>

namespace data = cista::raw;

static inline int numChannels(const std::string & encoding)
{
  if (encoding == "rgb8" ||
    encoding == "rgb8"   ||
    encoding == "bgr16"  ||
    encoding == "rgb16")
  {
    return 3;
  }
  if (encoding == "bgra8" ||
    encoding == "rgba8"   ||
    encoding == "bgra16"  ||
    encoding == "rgba16")
  {
    return 4;
  }

	throw std::runtime_error("Unknown or unsupported encoding " + encoding);
	return -1;
}

int main()
{
	struct _transport_img {
		uint32_t height;  // image height, that is, number of rows
		uint32_t width;   // image width, that is, number of columns
		data::string encoding; // types. Such as 'rgb8'
		data::vector<uint8_t> data;
	};

	using img_msg = struct _transport_img;

	img_msg test_data;
	uint8_t raw_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	test_data.encoding = "rgb8";
	test_data.height = 600;
	test_data.width = 300;
	test_data.data = data::vector<uint8_t>(raw_data, raw_data + sizeof(raw_data)/sizeof(raw_data[0]));

	std::vector<uint8_t> buf;
	{
		buf = cista::serialize(test_data);
	}

	auto deserialized = cista::deserialize<img_msg>(buf);
	assert(deserialized->height == 600);
	assert(deserialized->width == 300);
	assert(deserialized->encoding == "rgb8");

	for (auto & d : deserialized->data) {
		std::printf("%u\n", d);
	}

	return 0;
}
