classdef test_subclass < test_class
    
    properties
        y
        
    end
    
    properties (Dependent)
        
    end
    
    
    methods
        function obj = test_subclass(val1,val2)
            obj=obj@test_class(val1);
            obj.y=val2;
        end
    end
end