using System;

namespace tp1
{
	public class C3P0 : Droid
	{
		public C3P0 ()
		{
		}

		public override Void init ()
		{
			base.init();
			Console.WriteLine ("i'm a robot form a shity movie!");
		}
	}
}

