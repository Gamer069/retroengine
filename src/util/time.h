#pragma once

#include "ret_pch.h"

namespace RetroEngine {
	class Time {
	public:
           Time(float dt = 0.0f) : m_DeltaTime(dt) {}
           operator float() {
               return m_DeltaTime;
           }
           INLINE float GetDTInSeconds() const {
               return m_DeltaTime;
           }
           INLINE float GetDTInMillis() const {
   	       return m_DeltaTime * 1000.0f;
           }
           INLINE float GetDTInNanos() const {
                return m_DeltaTime * 1000000000.0f;
           }
       private:
      	    float m_DeltaTime;
	};
}