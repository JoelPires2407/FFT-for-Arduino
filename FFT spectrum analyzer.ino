unsigned short int N = 128;
short int s = 4096;

void fft(float *v_re ,float *v_im)
{
  unsigned short a = N / 2, j = 0, z, d = 1, i;
  int w_re[N/2], w_im[N/2];
  float re, im;
  for (i = 0 ; i  <  N - 1 ; i++)
  {
    if (j > i) {
      re = v_re[i];
      v_re[i] = v_re[j];
      v_re[j] = re;
    }
    z = N;
    while (j & (z >>= 1))
      j &= ~z;
    j |= z;
  }
  for (i = 1 ; i < N ; i<<=1)
  {
    for (int k = 0 ; k < N / a - d; k++)
    {
      w_re[k] =  s*cos((2 * 3.14 * k * a) / N);
      w_im[k] = - s*sin((2 *3.14 * k * a) / N);
    }
    z = 0;
    j = 0;
    while (j < N)
    {
      re = v_re[j];
      im = v_im[j];
      v_re[j] += (w_re[z] * v_re[j + d])/s - (w_im[z] * v_im[j + d])/s ;
      v_im[j] += (w_re[z] * v_im[j + d])/s  + (w_im[z] * v_re[j + d])/s ;
      v_re[j + d] = re - (w_re[z] * v_re[j + d])/s  + (w_im[z] * v_im[j + d])/s ;
      v_im[j + d] = im - (w_re[z] * v_im[j + d])/s  - (w_im[z] * v_re[j + d])/s;
      z++;
      j++;
      if (z == d)
      { 
        j += d;
        z = 0;
      }
    }
    d <<= 1;
    a >>= 1;
  }
  for (i = 0; i < N; i++)
  {
    Serial.println(sqrt(v_re[i]*v_re[i] + v_im[i]*v_im[i]));
  }
}
void setup()
{
  Serial.begin(9600);
  float v_re[N],v_im[N];
  for (unsigned short int i = 0; i < N; i++)
  {
    v_re[i] = sin(2*3.14*60*i*1000);
    v_im[i] = 0;
  }
  fft(v_re,v_im);
  
}
void loop() {
  
}
