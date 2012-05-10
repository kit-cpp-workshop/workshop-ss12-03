namespace bmp
{
	class BatchBitmap24;


	// A class implementing the IBatchDrawable interface
	// is drawable to a BatchBitmap24
	class IBatchDrawable
	{
	public:
		virtual ~IBatchDrawable() {}

		virtual bool applyTo(BatchBitmap24& p_target) = 0;
	};


	// never mind the following, it's black voodoo

	// NOTE: this WOULD be the definition of an interface
	//       that would be implemented by classes that can be drawn to a simple Bitmap24
	//       but we leave that out and come back later, it causes a slightly unpleasant problem
	//       (you could solve this with private and virtual inheritance)
	// A class implementing the IDrawable interface
	// is drawable to both, a BatchBitmap24 but also a simple Bitmap24
	/*class IDrawable
		: public virtual IBatchDrawable
	{
	public:
		virtual ~IDrawable() {}

		// this function remaps calls with a BatchBitmap24 parameter to the virtual function
		// defined in this interface (with parameter Bitmap24)
		// !!!!DON'T YOU OVERRIDE ME!!!!
		virtual bool applyTo(BatchBitmap24& p_target)	// FINAL
		{
			// NOTE: a static cast *should* work here too, but I don't trust anyone :P
			return applyTo( dynamic_cast<Bitmap24&>(p_target) );
		}

		// implement me!
		virtual bool applyTo(Bitmap24&) = 0;
	};*/
}
