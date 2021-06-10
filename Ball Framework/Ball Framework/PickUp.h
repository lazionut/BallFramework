#pragma once

#include <functional>
#include <thread>
#include "Paddle.h"
#include "Ball.h"
#include "Actions.h"

namespace BallFramework
{
	class PickUp : public Ball
	{
	public:
		friend class PickUpGenerator;

		PickUp() noexcept;
		PickUp(std::function<void()> startAction, const Vector2& position, const float size, const Vector2& direction, float speed) noexcept;
		PickUp(std::function<void()> startAction, std::function<void()> stopAction) noexcept;

		bool IsMoving() const noexcept;
		bool IsActionActive() const noexcept;
		Actions GetActionType() const noexcept;

		void SetActionType(Actions action) noexcept;
		void SetStartAction(std::function<void()> action);
		void SetStopAction(std::function<void()> action);
		void SetActions(std::function<void()> startAction, std::function<void()> stopAction, float time = 0.0f);

		void InvokeAction();
		bool ContinueAction();

		void StartMoving();

	private:
		std::function<void()> m_startAction;
		std::function<void()> m_StopAction;
		float m_time;
		float m_StopTime;

		bool m_isActionActive;
		bool m_isMoving;

		Actions m_actionType;
	};
}