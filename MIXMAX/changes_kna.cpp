//-------------------------------------------------------------------------------------
// Changes by Konstantinos N. Anagnostopoulos on 161126:
// Adding interface for saving/reading an engine's state. See example_checkpointing.cpp
// See also:
// > diff mixmax.cpp mixmax_v200beta.cpp
// > diff mixmax.hpp mixmax_v200beta.hpp
// ------------------------------------------------------------------------------------
//In mixmax.hpp:

class mixmax_engine: public _Generator<std::uint64_t, 0, 0x1FFFFFFFFFFFFFFF> // does not work with any other values
{
  //..............
  
    void print_state(std::ostream& ost);
    void print_state(const char* filename);
    void read_state (std::istream& ist);
    void read_state (const char  filename[] );
    friend std::ostream& operator<<(std::ostream& ost,const mixmax_engine& eng);
    friend std::istream& operator>>(std::istream& ist,      mixmax_engine& eng);
  //..............
}

//================================================================================================
//In mixmax.cpp:
  
void mixmax_engine::print_state(const char* filename){ // (std::ostream& ost){
    int j;
    FILE *fp;
    fp = fopen(filename,"w");
    fprintf(fp, "%u ", rng_get_N() );
    for (j=0; (j< (rng_get_N()-1) ); j++) {
        fprintf(fp, "%llu ", S.V[j] );
    }
    fprintf(fp, "%llu " , S.V[rng_get_N()-1] );
    fprintf(fp, "%u "   , S.counter );
    fprintf(fp, "%llu\n", S.sumtot );
    fclose(fp);
}

void mixmax_engine::print_state(std::ostream& ost){
    int j;
    ost << rng_get_N() << " ";
    for (j=0; (j< (rng_get_N()-1) ); j++) {
      ost << S.V[j] << " ";
    }
    ost << S.V[rng_get_N()-1] << " ";
    ost << S.counter          << " ";
    ost << S.sumtot           << std::endl;
}

std::ostream& operator<<(std::ostream& ost,const mixmax_engine& eng){
    int j;
    ost   << eng.rng_get_N() << " ";
    for (j=0; (j< (eng.rng_get_N()-1) ); j++) {
      ost << eng.S.V[j] << " ";
    }
    ost   << eng.S.V[eng.rng_get_N()-1] << " ";
    ost   << eng.S.counter              << " ";
    ost   << eng.S.sumtot;
    return ost;
}
void mixmax_engine::read_state(std::istream& ist){
    int j;
    int Nread;
    ist >> Nread;
    if(Nread != rng_get_N()){
      std::cerr << "read_state: FATAL ERROR Nread= " << Nread
                << "!= N= " << rng_get_N()
                << ".Exiting...." << std::endl;
      exit(1);
    }
    for (j=0; (j< (rng_get_N()-1) ); j++) {
      ist >> S.V[j];
    }
    ist >> S.V[rng_get_N()-1];
    ist >> S.counter;
    ist >> S.sumtot;
}

std::istream& operator>> (std::istream& ist, mixmax_engine& eng){
    int j;
    int Nread;
    ist   >> Nread;
    if(Nread != eng.rng_get_N()){
      std::cerr << "read_state: FATAL ERROR Nread= " << Nread
                << "!= N= "                          << eng.rng_get_N()
                << ".Exiting...."                    << std::endl;
      exit(1);
    }
    for (j=0; (j< (eng.rng_get_N()-1) ); j++) {
      ist >> eng.S.V[j];
    }
    ist   >> eng.S.V[eng.rng_get_N()-1];
    ist   >> eng.S.counter;
    ist   >> eng.S.sumtot;
    return ist;
}
void mixmax_engine::read_state(const char* filename){ // (std::ostream& ost){
    int j;
    FILE *fp;
    int Nread;
    fp = fopen(filename,"r");
    fscanf(fp, "%u ", &Nread );
    if(Nread != rng_get_N()){
      fprintf(stderr,"read_state: FATAL ERROR Nread= %d != N= %d. Exiting...\n",Nread,rng_get_N());
      exit(1);
    }
    for (j=0; (j< (rng_get_N()-1) ); j++) {
        fscanf(fp, "%llu ", &S.V[j] );
    }
    fscanf(fp, "%llu ", &S.V[rng_get_N()-1] );
    fscanf(fp, "%u "  , &S.counter );
    fscanf(fp, "%llu" , &S.sumtot );
    fclose(fp);
}

//========================================================================================
// Changes to get rid of the warnings: %llu format to %lu in:


void mixmax_engine::print_state(){ // (std::ostream& ost){
    int j;
    fprintf(stdout, "mixmax state, file version 1.0\n" );
    fprintf(stdout, "N=%u; V[N]={", rng_get_N() );
    for (j=0; (j< (rng_get_N()-1) ); j++) {
        fprintf(stdout, "%lu, ", S.V[j] );
    }
    fprintf(stdout, "%lu", S.V[rng_get_N()-1] );
    fprintf(stdout, "}; " );
    fprintf(stdout, "counter=%u; ", S.counter );
    fprintf(stdout, "sumtot=%lu;\n", S.sumtot );
}

void mixmax_engine::BranchDaughter(int b){ // valid values are between b=5 and b=60
    if(b>60) {std::cerr << "MIXMAX ERROR: " << "Disallowed value of parameter b in BranchDaughter\n"; exit(-1);}
    // Dont forget to branch mother, when you branch the daughter, or else you will have collisions!
    printf("V[N] = %lu, %d\n", S.V[N], b); S.V[N] ^= (1<<(BITS-b)); S.V[N] |= 1; printf("V[N] = %lu\n", S.V[N]);
    S.sumtot = iterate_raw_vec(S.V.data(), S.sumtot); printf("iterating!\n");
}
