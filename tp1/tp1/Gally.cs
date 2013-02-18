using System;

namespace tp1
{
	public class Gally : Droid
	{
		private static Gally myself = null;
		public static Gally getInstance()
		{
			if (myself == null)
				myself = new Gally();
			return (myself);
		}

		private Gally ()
		{
		}

		public override Void init ()
		{
			base.init();
			Console.WriteLine ("i fell your live go away, and soon see you hear break in my hand");
		}
	}
}

