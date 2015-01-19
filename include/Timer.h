#pragma once

#include <SDL2/SDL.h>

/*
	Fixed step timer
	The change it time (deltatime) is passed
	to Update method via function pointer and everything thing that
	happens in Update(doible) is dependent on deltatime
*/

class Timer
{
public:
	Timer(double idealFPS=60) { Reset(idealFPS); }

	void Reset(double idealFPS)
	{
		m_idealFPS = idealFPS;
		m_idealDeltaTime = 1/m_idealFPS;
		m_prevTime = SDL_GetTicks();
		m_secondCounter = m_fps = m_frameCounter = 0;
		m_accumulator = 0;
		m_precision = 1.0 / 4000.0f;
	}

	void Update(std::function<void(double)> update)
	{
		//get current time in ms
		double current_time = SDL_GetTicks();

		//calculate the elapsed time or delta time or time between two updates
		double delta_time = current_time - m_prevTime;

		//set previous time
		m_prevTime = current_time;

		// Second counter to keep track of whether we have crossed a second
        m_secondCounter += static_cast<uint32_t>(delta_time * 1000.0f);

		if (delta_time > 1)
        	delta_time = 1;

        //RIP small errors
        if(fabs(delta_time - m_idealDeltaTime) < m_precision)
        	delta_time = m_idealDeltaTime;



		/*
		we may have some unsimulated time left over at the end of each frame
		due to the lag or boost in CPU process
		so to compensate that we use thie accumulator value

		This left over time is passed on to the next 
		frame via the accumulator variable and is not thrown away.
		
		update a frame by the ideal delta time: 
		if more time has passed than ideal delta time, update more than once
        since ideal delta time is constant, 
        using ideal delta time instead of observed delta time ensures constant output on multiple devices
        */
		m_accumulator += delta_time;

		// For current second, one more frame has passed
        if (m_accumulator >= m_idealDeltaTime)
            ++m_frameCounter;

		while(m_accumulator >= m_idealDeltaTime)
		{
			m_accumulator -= m_idealDeltaTime;
			update(m_idealDeltaTime);
		}

		 // Calculate FPS using frameCounter and secondCounter
        if (m_secondCounter > 1000)
        {
            m_fps = m_frameCounter;
            m_frameCounter = 0;
            m_secondCounter %= 1000;
        }
	}

	uint32_t GetFPS() { return m_fps; }

private:
	double m_precision;
	double m_idealFPS, m_idealDeltaTime, m_prevTime, m_accumulator;
	uint32_t m_fps, m_frameCounter, m_secondCounter;
};