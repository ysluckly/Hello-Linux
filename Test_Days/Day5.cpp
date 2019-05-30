#### 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
sort(nums.begin(),nums.end()); int len = nums.size(); vector<vector<int>> ans; if(nums.empty()) return {}; 
        for(int i = 0;i < len;++i){

        if(i > 0 && nums[i] == nums[i-1]) continue;
        int newtar = -nums[i];//转换成两数之和的目标值
        int j = i + 1;
        int k = len-1;
        while(j < k)
        {
            if(nums[j] + nums[k] == newtar)
            {
                ans.push_back({nums[i],nums[j],nums[k]});
                
                while(j < k && nums[j] == nums[j + 1]) ++j;
                while(j < k && nums[k] == nums[k - 1]) --k;
                j++;
                --k;
            }
            else if(nums[j] + nums[k] < newtar) j++;
            else k--;
        }
    }
    return ans;
    }
};
