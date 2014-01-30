function bio=xpcoscbio
bio = [];
bio(1).blkName='Gain';
bio(1).sigName='';
bio(1).portIdx=0;
bio(1).dim=[1,1];
bio(1).sigWidth=1;
bio(1).sigAddress='&xpcosc_B.Gain';
bio(1).ndims=2;
bio(1).size=[];

bio(getlenBIO) = bio(1);

bio(2).blkName='Gain1';
bio(2).sigName='';
bio(2).portIdx=0;
bio(2).dim=[1,1];
bio(2).sigWidth=1;
bio(2).sigAddress='&xpcosc_B.Gain1';
bio(2).ndims=2;
bio(2).size=[];


bio(3).blkName='Gain2';
bio(3).sigName='';
bio(3).portIdx=0;
bio(3).dim=[1,1];
bio(3).sigWidth=1;
bio(3).sigAddress='&xpcosc_B.Gain2';
bio(3).ndims=2;
bio(3).size=[];


bio(4).blkName='Integrator';
bio(4).sigName='';
bio(4).portIdx=0;
bio(4).dim=[1,1];
bio(4).sigWidth=1;
bio(4).sigAddress='&xpcosc_B.Integrator';
bio(4).ndims=2;
bio(4).size=[];


bio(5).blkName='Integrator1';
bio(5).sigName='';
bio(5).portIdx=0;
bio(5).dim=[1,1];
bio(5).sigWidth=1;
bio(5).sigAddress='&xpcosc_B.Integrator1';
bio(5).ndims=2;
bio(5).size=[];


bio(6).blkName='Signal Generator';
bio(6).sigName='';
bio(6).portIdx=0;
bio(6).dim=[1,1];
bio(6).sigWidth=1;
bio(6).sigAddress='&xpcosc_B.SignalGenerator';
bio(6).ndims=2;
bio(6).size=[];


bio(7).blkName='Sum';
bio(7).sigName='';
bio(7).portIdx=0;
bio(7).dim=[1,1];
bio(7).sigWidth=1;
bio(7).sigAddress='&xpcosc_B.Sum';
bio(7).ndims=2;
bio(7).size=[];


function len = getlenBIO
len = 7;

