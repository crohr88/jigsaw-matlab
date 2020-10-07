function [dcos] = triang2(pp,t2)
%TRIANG2 calc. enclosed angles for a 2-simplex triangulation
%embedded in euclidean space.
%   [ADEG] = TRIANG2(VERT,TRIA) returns the enclosed angles
%   associated with each triangle, where ADEG is a T-by-3
%   array of the angles subtended at each vertex, VERT is a
%   V-by-2 array of XY coordinates, and TRIA is a T-by-3 ar-
%   ray of vertex indexing, where each row defines a triang-
%   le, such that VERT(TRIA(II,1),:), VERT(TRIA(II,2),:) and
%   VERT(TRIA(II,3),:) are the coordinates of the II-TH tri-
%   angle. Angles are returned in degrees.
%
%   See also TRISCR2, TRIVOL2, TRIBAL2

%   Darren Engwirda : 2017 --
%   Email           : d.engwirda@gmail.com
%   Last updated    : 08/07/2018

%---------------------------------------------- basic checks
    if (~isnumeric(pp) || ~isnumeric(t2) )
        error('triang2:incorrectInputClass' , ...
            'Incorrect input class.') ;
    end

%---------------------------------------------- basic checks
    if (ndims(pp) ~= +2 || ndims(t2) ~= +2 )
        error('triang2:incorrectDimensions' , ...
            'Incorrect input dimensions.');
    end
    if (size(pp,2) < +2 || size(t2,2) < +3 )
        error('triang2:incorrectDimensions' , ...
            'Incorrect input dimensions.');
    end

    nnod = size(pp,1) ;

%---------------------------------------------- basic checks
    if (min(min(t2(:,1:3))) < +1 || ...
            max(max(t2(:,1:3))) > nnod )
        error('triang2:invalidInputs', ...
            'Invalid TRIA input array.') ;
    end

%----------------------------------- compute enclosed angles
    dcos = zeros(size(t2,1),3) ;

    ev12 = pp(t2(:,2),:)-pp(t2(:,1),:) ;
    ev23 = pp(t2(:,3),:)-pp(t2(:,2),:) ;
    ev31 = pp(t2(:,1),:)-pp(t2(:,3),:) ;

    lv11 = sqrt(sum(ev12.^2,2));
    lv22 = sqrt(sum(ev23.^2,2));
    lv33 = sqrt(sum(ev31.^2,2));

    ev12 = ev12 ./ ...
        lv11(:,ones(1,size(pp,2)));
    ev23 = ev23 ./ ...
        lv22(:,ones(1,size(pp,2)));
    ev31 = ev31 ./ ...
        lv33(:,ones(1,size(pp,2)));

    dcos(:,1) = sum(-ev12.*ev23,2);
    dcos(:,2) = sum(-ev23.*ev31,2);
    dcos(:,3) = sum(-ev31.*ev12,2);

    dcos(:,1) = max(-1.,dcos(:,1));
    dcos(:,1) = min(+1.,dcos(:,1));
    dcos(:,2) = max(-1.,dcos(:,2));
    dcos(:,2) = min(+1.,dcos(:,2));
    dcos(:,3) = max(-1.,dcos(:,3));
    dcos(:,3) = min(+1.,dcos(:,3));

    dcos = acos(dcos) * 180. / pi ;

end


