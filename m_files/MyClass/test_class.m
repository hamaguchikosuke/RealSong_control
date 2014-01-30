classdef test_class < handle
    
    properties
       x
        
    end
    
    properties (Dependent)
        
    end
    
    
    methods
        function obj = test_class(val)
            obj.x=val;
        end
    end
end