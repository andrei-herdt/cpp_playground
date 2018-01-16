#ifndef STATEMACHINE_DEFINITION_H
#define STATEMACHINE_DEFINITION_H

#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include "statemachine_events.h"

namespace statemachine
{

namespace msm = boost::msm;
namespace msmf = boost::msm::front;
namespace mpl = boost::mpl;

// ----- State machine
struct Frontend : msmf::state_machine_def<Frontend>
{
    // States
    struct Init : msmf::state<>
    {
        // Entry action
        template <class Event, class Fsm>
        void on_entry(const Event&, Fsm&) const
        {
            std::cout << "Init::on_entry()" << std::endl;
        }
    };

    struct On : msmf::state<>
    {
        // Entry action
        template <class Event, class Fsm>
        void on_entry(const Event&, Fsm&) const
        {
            std::cout << "On::on_entry()" << std::endl;
        }
    };

    struct Off : msmf::state<>
    {
        // Entry action
        template <class Event, class Fsm>
        void on_entry(const Event&, Fsm&) const
        {
            std::cout << "Off::on_entry()" << std::endl;
        }
    };

    // override no_transition to do nothing
    template <class Event, class Fsm>
    void no_transition(const Event&, Fsm&, int /* state */)
    {
        // Do nothing if an event doesn't lead to a transition instead of assert(false)
    }

    // Guards
    struct ActivationGuard
    {
        template <class Fsm>
        bool operator()(const ActivationEvent& activation, Fsm&, Off&, On&) const
        {
            return activation.IsAllowed();
        }
    };

    // Set initial state
    typedef Init initial_state;

    // Transition table
    struct transition_table : mpl::vector<
                                  // clang-format off
                                  //      Start  , Event             , Next , Action     , Guard
                                  msmf::Row<Init , msmf::none        , Off  , msmf::none , msmf::none>      ,
                                  msmf::Row<Off  , ActivationEvent   , On   , msmf::none , ActivationGuard> ,
                                  msmf::Row<On   , DeactivationEvent , Off  , msmf::none , msmf::none>
                                  // clang-format on
                                  >
    {
    };
};

// Pick a back-end
typedef msm::back::state_machine<Frontend> OnOffMachine;

}  // namespace statemachine

#endif /* STATEMACHINE_DEFINITION_H */