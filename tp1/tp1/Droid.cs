using System;

namespace tp1
{
	public abstract class Droid
	{
		private	bool hasBeenInit = false;
		public Droid ()
		{
		}
		virtual public Void init() {
			hasBeenInit = true;
			Console.WriteLine ("i'm alive!");
		}
		public bool work() {
				if(!hasBeenInit)
					return false;
				Console.WriteLine ("i'm still alive!");
				return true;
			}
		public Void shutdown() {
			if (!hasBeenInit)
			{
				Console.WriteLine ("mechanique switch off!");
				goto end;
			}
			Console.WriteLine ("i'm not alive!");
		end:
				return;
		}
	}
}

