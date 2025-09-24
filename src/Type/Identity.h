#pragma once
#ifndef SCL_META_IDENTITY_H

#include "Sequence.h"

namespace ScL::Meta
{
    //! Define type value as _Type (collection for only one type).
    template <typename _Type>
    using Identity = Sequence<_Type>;
} // namespace ScL::Meta

#endif
