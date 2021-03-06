//
// immer - immutable data structures for C++
// Copyright (C) 2016 Juan Pedro Bolivar Puente
//
// This file is part of immer.
//
// immer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// immer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with immer.  If not, see <http://www.gnu.org/licenses/>.
//

#pragma once

#include <immer/heap/heap_policy.hpp>
#include <immer/refcount/refcount_policy.hpp>
#include <type_traits>

namespace immer {

/*!
 * This is a default implementation of a *memory policy*.  A memory
 * policy is just a bag of other policies plus some flags with hints
 * to the user about the best way to use these strategies.
 *
 * @tparam HeapPolicy A *heap policy*, for example, @ref heap_policy.
 * @tparam RefcountPolicy A *reference counting policy*, for example,
 *         @ref refcount_policy.
 * @tparam PreferFewerBiggerObjects Boolean flag indicating whether
 *         the user should prefer to allocate memory in bigger chungs
 *         --e.g. by putting various objects in the same memory
 *         region-- or not.
 */
template <typename HeapPolicy,
          typename RefcountPolicy,
          bool PreferFewerBiggerObjects = !std::is_same<
              HeapPolicy,
              free_list_heap_policy<malloc_heap>>()>
struct memory_policy
{
    using heap     = HeapPolicy;
    using refcount = RefcountPolicy;

    static constexpr bool prefer_fewer_bigger_objects =
        PreferFewerBiggerObjects;
};

/*!
 * The default *heap policy* just uses the standard heap.  If
 * `IMMER_FREE_LIST` is defined to `1` then it uses the special @ref
 * free_list_heap_policy.
 */
#if IMMER_FREE_LIST
using default_heap_policy = free_list_heap_policy<malloc_heap>;
#else
using default_heap_policy = heap_policy<malloc_heap>;
#endif

/*!
 * By default we use thread safe reference counting.
 */
using default_refcount_policy = refcount_policy;

/*!
 * The default memory policy.
 */
using default_memory_policy = memory_policy<
    default_heap_policy,
    default_refcount_policy>;

} // namespace immer
