////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2023 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Aditya Mukhopadhyay
////////////////////////////////////////////////////////////////////////////////

#include "InitialState.h"

#include "CreateWorkersState.h"
#include "Pregel/Conductor/State.h"
#include "Pregel/Conductor/ExecutionStates/FatalErrorState.h"

using namespace arangodb;
using namespace arangodb::pregel;
using namespace arangodb::pregel::conductor;

Initial::Initial(ConductorState& conductor) : conductor{conductor} {}

auto Initial::receive(actor::ActorPID sender,
                      message::ConductorMessages message)
    -> std::optional<StateChange> {
  if (!std::holds_alternative<message::ConductorStart>(message)) {
    auto newState = std::make_unique<FatalError>(conductor);
    auto stateName = newState->name();
    return StateChange{
        .statusMessage = pregel::message::InFatalError{.state = stateName},
        .newState = std::move(newState)};
  }

  auto newState = std::make_unique<CreateWorkers>(conductor);
  auto stateName = newState->name();

  return StateChange{
      .statusMessage = pregel::message::PregelStarted{.state = stateName},
      .newState = std::move(newState)};
}
