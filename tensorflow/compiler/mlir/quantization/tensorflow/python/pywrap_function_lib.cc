/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "pybind11/detail/common.h"  // from @pybind11
#include "pybind11/pybind11.h"  // from @pybind11
#include "tensorflow/compiler/mlir/quantization/tensorflow/exported_model.pb.h"
#include "tensorflow/compiler/mlir/quantization/tensorflow/python/py_function_lib.h"
#include "tensorflow/compiler/mlir/quantization/tensorflow/python/type_casters.h"
#include "tensorflow/python/lib/core/pybind11_lib.h"

namespace {

using ::tensorflow::quantization::ExportedModel;
using ::tensorflow::quantization::PyFunctionLibrary;

// A "trampoline" class that redirects virtual function calls to the python
// implementation.
//
// Reference:
// https://pybind11.readthedocs.io/en/stable/advanced/classes.html#overriding-virtual-functions-in-python
class PyFunctionLibraryTrampoline : public PyFunctionLibrary {
 public:
  using PyFunctionLibrary::PyFunctionLibrary;

  ExportedModel AssignIdsToCustomAggregatorOps(
      const ExportedModel& exported_model) const override {
    PYBIND11_OVERRIDE_PURE(ExportedModel, PyFunctionLibrary,
                           assign_ids_to_custom_aggregator_ops, exported_model);
  }
};

}  // namespace

PYBIND11_MODULE(pywrap_function_lib, m) {
  py::class_<PyFunctionLibrary, PyFunctionLibraryTrampoline>(
      m, "PyFunctionLibrary")
      .def(py::init<>())
      .def("assign_ids_to_custom_aggregator_ops",
           &PyFunctionLibrary::AssignIdsToCustomAggregatorOps);
}
