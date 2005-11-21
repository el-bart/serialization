#ifndef BOOST_SERIALIZATION_VALARAY_HPP
#define BOOST_SERIALIZATION_VALARAY_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector.hpp: serialization for stl vector templates

// (C) Copyright 2005 Matthias Troyer . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <valarray>

#include <boost/config.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/save_array.hpp>
#include <boost/serialization/load_array.hpp>
#include <boost/serialization/detail/get_data.hpp>

// function specializations must be defined in the appropriate
// namespace - boost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace boost { namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// valarray<T>

template<class Archive, class U>
void save( Archive & ar, const STD::valarray<U> &t, const unsigned int file_version )
{
  const boost::archive::container_size_type count(t.size());
  ar << BOOST_SERIALIZATION_NVP(count);
  if (count)
    save_array(ar, detail::get_data(t), t.size(), file_version);
}


template<class Archive, class U>
void load( Archive & ar, STD::valarray<U> &t,  const unsigned int file_version )
{
  boost::archive::container_size_type count;
  ar >> BOOST_SERIALIZATION_NVP(count);
  t.resize(count);
  if (count)
    load_array(ar, detail::get_data(t), t.size(), file_version);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U>
inline void serialize( Archive & ar, STD::valarray<U> & t, const unsigned int file_version)
{
    boost::serialization::split_free(ar, t, file_version);
}

} } // end namespace boost::serialization

#include <boost/serialization/collection_traits.hpp>

BOOST_SERIALIZATION_COLLECTION_TRAITS(STD::valarray)
#undef STD

#endif // BOOST_SERIALIZATION_VALARAY_HPP