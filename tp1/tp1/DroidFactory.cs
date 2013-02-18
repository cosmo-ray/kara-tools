using System;

namespace tp1
{
//
//	public class genDroid<T>
//	{
//		T	type;
//
//		genDroid (Type type)
//		{
//		}
//	}

	static public class DroidFactory
	{
		static public T creatDroid<T>()
			where T : Droid, new()
		{
			return (new T());
		}
	}
}

