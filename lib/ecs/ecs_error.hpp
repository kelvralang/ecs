#pragma once

#include <cstdint>

namespace kelvra::ecs {

enum class EcsErrorCode : std::uint32_t {
    Ok = 0,
    InvalidWorld,
    InvalidQuery,
    InvalidEntity,
    StaleEntity,
    InvalidComponentType,
    ComponentAlreadyExists,
    ComponentNotFound,
    InvalidComponentSize,
    InvalidAlignment,
    QueryInvalidated,
    InvalidArgument,
    OutOfMemory,
    InternalError,
    ComponentTypeConflict,
};

}  // namespace kelvra::ecs
