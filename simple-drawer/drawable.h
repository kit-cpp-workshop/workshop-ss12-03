namespace bmp
{
	class BatchBitmap24;

	class Drawable
	{
	public:
		virtual ~Drawable() {}

		virtual bool apply(BatchBitmap24&) = 0;
	};
}
