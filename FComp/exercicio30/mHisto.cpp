{
  int a[2];
  for(int i = 0; i < 2; i++)
    cout<<"a["<<i<<"] = "<<a[i]<<endl;

  TH1F *h[2] = {new TH1F("h1", "histogram1",10, 0.5, 10.5), new TH1F("h2", "histogram2",10, 0.5, 10.5)};

  Float_t *xbins = new Float_t[5];
  xbins[0] = 0.5;
  xbins[1] = 1.0;
  xbins[2] = 1.5;
  xbins[3] = 2.0;
  xbins[4] = 4.5;

  TH1F *h1[2] = {new TH1F("h11", "histogram1", 4, xbins),
                 new TH1F("h12", "histogram2", 4, xbins)};

  TH1F *h2[2];
  h2[0] = new TH1F("h21", "histogram1", 10, 0.5, 10.5);
  h2[1] = new TH1F("h22", "histogram2", 10, 0.5, 10.5);

  TH1F **p[2] = {new TH1F*[2], new TH1F*[2]};
  p[0] = h;
  p[1] = h2
}
