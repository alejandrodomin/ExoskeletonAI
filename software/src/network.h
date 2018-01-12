#ifdef
#ifndef  // this iffy

class Net
{
   private:
   protected:
      int **nodes;
   public:
      Net();
      ~Net(); // destructor deletes heap memory
      bool rand_node();
      bool rand_connection();
};

#endif