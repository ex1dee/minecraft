#ifndef UUIDWRAPPER_H
#define UUIDWRAPPER_H

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <string>

class UUIDWrapper {
	boost::uuids::uuid data;
	std::string str;
public:
	UUIDWrapper() : data(boost::uuids::random_generator()()), str(boost::uuids::to_string(data)) {}

	bool operator==(const UUIDWrapper& other) const { return data == other.data; }
	bool operator!=(const UUIDWrapper& other) const { return !operator==(other); }

	const std::string& toString() const { return str; }
};

#endif