
#include "svc_tier_rados.h"

const std::string MP_META_SUFFIX = ".meta";

bool MultipartMetaFilter::filter(const string& name, string& key) {
  // the length of the suffix so we can skip past it
  static const size_t MP_META_SUFFIX_LEN = MP_META_SUFFIX.length();

  size_t len = name.size();

  // make sure there's room for suffix plus at least one more
  // character
  if (len <= MP_META_SUFFIX_LEN)
    return false;

  size_t pos = name.find(MP_META_SUFFIX, len - MP_META_SUFFIX_LEN);
  if (pos == string::npos)
    return false;

  pos = name.rfind('.', pos - 1);
  if (pos == string::npos)
    return false;

  key = name.substr(0, pos);

  return true;
}

