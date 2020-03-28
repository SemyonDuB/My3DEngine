#pragma once

namespace SGE
{
	class BaseScene
	{
		virtual void initializeScene();
		virtual void add_obj() = 0;
		virtual void delete_obj() = 0;

		virtual ~BaseScene();
	};
}
