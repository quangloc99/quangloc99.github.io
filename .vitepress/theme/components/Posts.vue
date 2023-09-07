<script lang="ts" setup>
import { data as posts } from "../static-data/posts.data";
import PostItem from "./PostItem.vue";
</script>

<template>
  <div v-for="post in posts">
    <PostItem
      :title="post.title"
      :date="post.date"
      :url="post.url"
      :excerpt="post.excerpt"
    />
  </div>
</template>
