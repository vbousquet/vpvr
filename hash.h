#pragma once

// this is the djb2 string hash algorithm, str is converted to lower case
inline size_t StringHash(const string& str)
{
   //MessageBox(0, str, 0, 0);
   unsigned int hash = 5381;

   const size_t l = str.length();
   for (size_t i = 0; i < l; ++i)
      hash = ((hash << 5) + hash) + tolower(str[i]); /* hash * 33 + str[i] */

   return hash;
}

// very simple hash, but good enough so far for the obj loader (i.e. hash gen speed matters!)
template <size_t T>
size_t FloatHash(const float a[T])
{
   const unsigned char *in = reinterpret_cast<const unsigned char*>(a);
   unsigned int ret = 2654435761u;
   for (size_t i = 0; i < (T * sizeof(float)); ++i)
      ret = (ret * 2654435761u) ^ *in++;
   
   return ret;
}

struct StringHashFunctor
{
   size_t operator()(const string& str) const
   {
      // use case-insensitive hash because user can enter the names in lower case from the script
      return StringHash(str);
   }
};

struct StringComparator
{
   bool operator()(const string& str1, const string& str2) const
   {
      // use case-insensitive compare because user can enter the names in lower case from the script
      return lstrcmpi(str1.c_str(), str2.c_str()) == 0;
   }
};

//

// ignores Idx-int completely!
struct Vertex3D_NoTex2IdxHashFunctor
{
   size_t operator()(const std::pair<const Vertex3D_NoTex2*,const unsigned int>& a) const
   {
      return FloatHash<sizeof(Vertex3D_NoTex2)/sizeof(float)>((const float*)a.first);
   }
};

// ignores Idx-int completely!
struct Vertex3D_NoTex2IdxComparator
{
   bool operator()(const std::pair<const Vertex3D_NoTex2*,const unsigned int>& a, const std::pair<const Vertex3D_NoTex2*,const unsigned int>& b) const
   {
      return memcmp(a.first, b.first, sizeof(Vertex3D_NoTex2)) == 0;
   }
};

namespace robin_hood {
template<>
struct hash<robin_hood::pair<unsigned, unsigned>> {
   size_t operator()(robin_hood::pair<unsigned, unsigned> const& p) const noexcept {
      return hash<unsigned long long>{}((unsigned long long)p.first | (((unsigned long long)p.second) << 32));
   }
};
template<>
struct hash<robin_hood::pair<int, int>> {
   size_t operator()(robin_hood::pair<int, int> const& p) const noexcept {
      return hash<unsigned long long>{}((unsigned long long)(unsigned int)p.first | (((unsigned long long)(unsigned int)p.second) << 32));
   }
};
}
