#ifndef TYPE_HEIGHT_MAP
#define TYPE_HEIGHT_MAP

typedef sf::Vector2<long long> vector2ll;

#define SIDE_LENGTH_TYPE int
#define HEIGHT_TYPE int

struct HeightCoord
{
  long long x;
  long long y;
  SIDE_LENGTH_TYPE side;

  bool operator<(const HeightCoord& b) const { return std::tie(x, y, side) < std::tie(b.x, b.y, b.side); }
  bool operator>(const HeightCoord& b) const { return std::tie(x, y, side) > std::tie(b.x, b.y, b.side); }
};

class HeightMap
{
public:
  // returns the sum of the heights of side=1 to side=HEIGHT_CHUNK_SIZE.
  HEIGHT_TYPE height( long long x, long long y );

  // generates all required levels to generate x,y,side.
  void generate( long long x, long long y );

private:
  std::map< HeightCoord, HEIGHT_TYPE > data;

  // returns the Coords of x,y,side in data. always use this to get the position of any element!
  HeightCoord at( long long x, long long y, SIDE_LENGTH_TYPE side );

  // returns the height of x,y,side.
  HEIGHT_TYPE& get( HeightCoord& p );

  // sets the height value for the side length of x and y.
  void set( HeightCoord p, HEIGHT_TYPE value );
};

#endif // TYPE_HEIGHT_MAP