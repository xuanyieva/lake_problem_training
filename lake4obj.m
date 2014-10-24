%LakeProblem_4Obj_1Const_Stoch
%Xuan Yi, Oct, 2014
%Peking University, Cornell University
%xuanyi.eva@gmail.com
%Adapted from Riddhi Singh and Tori Ward, LakeProblem_4Obj_1Const_Stoch.cpp




function[objs constrs]=lake4obj(decision)
nvars=100;%decision variables
nobjs=4;
nconstrs=1;
nSamples=100;%100 samples of the natture inflows
b      = 0.42;%decay reate form P in lake
q      = 2;%recycling exponent
alpha  = 0.4;%utility from pollution
delta  = 0.98;%descount rate
permit=0.5;
ine_threshold=-0.02;%the change between each step much >-.02
reli_threshold=0.95;%for constraints

aver_dailyX=zeros(1,nvars);
benefits=zeros(1,nSamples);
obj3=0;
obj4=0;
for i=1:nSamples
    
    nat_flow=lognrnd(-3.52,0.105,1,nvars);
    lake_stateX0=0;
    
    for t=1:nvars
        if t==1
            lake_stateX(t)=lake_stateX0*(1-b)+(lake_stateX0^q/(1+lake_stateX0^q))+nat_flow(t)+decision(t);
        else
        lake_stateX(t)=lake_stateX(t-1)*(1-b)+( lake_stateX(t-1)^q/(1+ lake_stateX(t-1)^q))+nat_flow(t)+decision(t);
        end
        aver_dailyX(t)=aver_dailyX(t)+lake_stateX(t)/nSamples;
        benefits(i)=benefits(i)+delta*decision(t)*delta^t;%accumulation each sample's discounted benefits

    end
    obj3=obj3+length(find(lake_stateX<permit));
    obj4=obj4+length(find(diff(lake_stateX)>ine_threshold));
end

obj1=max(aver_dailyX);%find the maximum average daily Phosphorous all over the samples
obj2=sum(benefits)/nSamples;%Maximize the average sum of discounted benefits
obj3=obj3/nSamples/nvars;%Maximize timesteps satisfying X < Pmermit
obj4=obj4/((nSamples-1)*nvars);%Maximize timesteps meeting inertia threshold

objs=[obj1 -1*obj2 -1*obj3 -1*obj4];

if obj3>reli_threshold
   constrs=0.0;
else
    constrs=reli_threshold-obj3;
end
end




        
        
        
